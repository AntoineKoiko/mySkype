#include <cstdio>
#include <stdlib.h>
#include "portaudio.h"
#include "Audio.hpp"

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS (5)
#define NUM_CHANNELS (2)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG (0)

#define WRITE_TO_FILE (0)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE (128)
#define PRINTF_S_FORMAT "%d"
#endif

typedef struct
{
    int frameIndex; /* Index into sample array. */
    int maxFrameIndex;
    SAMPLE *recordedSamples;
} paTestData;

/* This routine will be called by the PortAudio engine when audio is needed.
    ** It may be called at interrupt level on some machines so don't do anything
    ** that could mess up the system like calling malloc() or free().
    */
int recordCallback(const void *inputBuffer, [[maybe_unused]] void *outputBuffer,
                   unsigned long framesPerBuffer,
                   [[maybe_unused]] const PaStreamCallbackTimeInfo *timeInfo,
                   [[maybe_unused]] PaStreamCallbackFlags statusFlags,
                   void *userData)
{
    //ON RECUP LA STRUCTURE DU USER (pouvant contenir 5seconds de son à 44khz)
    paTestData *data = (paTestData *)userData;

    //rptr contient l'enregistrement du micro
    const SAMPLE *rptr = (const SAMPLE *)inputBuffer;

    //NOTRE BUFFER DE DATA
    SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    long framesToCalc;
    long i;
    int finished;
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex; //LE NOMBRE DE FRAME QU'IL RESTE A STOCKER

    if (framesLeft < framesPerBuffer)
    {                              //SI + de frames dans le buffer que de place restante
        framesToCalc = framesLeft; //on va traiter le nombre de frame restante
        finished = paComplete;     //on indique que la callback est fini
    }
    else
    {                                   //SINON
        framesToCalc = framesPerBuffer; //ON VA TRAITER TOUTES LES FRAMES DU BUFFER
        finished = paContinue;          //ON CONTINUE LA CALLBACK
    }

    if (inputBuffer == NULL)
    { //SI LE BUFFER EST NULL ALORS  ON LE REMPLIS AVEC RIEN
        for (i = 0; i < framesToCalc; i++)
        {
            *wptr++ = SAMPLE_SILENCE; /* left */
            if (NUM_CHANNELS == 2)
                *wptr++ = SAMPLE_SILENCE; /* right */
        }
    }
    else
    {
        for (i = 0; i < framesToCalc; i++)
        {
            *wptr++ = *rptr++; /* left */
            if (NUM_CHANNELS == 2)
                *wptr++ = *rptr++; /* right */
        }
    }
    data->frameIndex += framesToCalc;
    return finished;
}

/* This routine will be called by the PortAudio engine when audio is needed.
   ** It may be called at interrupt level on some machines so don't do anything
   ** that could mess up the system like calling malloc() or free().
   */
int playCallback([[maybe_unused]] const void *inputBuffer, void *outputBuffer,
                 unsigned long framesPerBuffer,
                 [[maybe_unused]] const PaStreamCallbackTimeInfo *timeInfo,
                 [[maybe_unused]] PaStreamCallbackFlags statusFlags,
                 void *userData)
{
    paTestData *data = (paTestData *)userData;
    SAMPLE *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    SAMPLE *wptr = (SAMPLE *)outputBuffer;
    unsigned int i;
    int finished;
    unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

    if (framesLeft < framesPerBuffer)
    { //LE NOMBRE DE FRAMES RESTANTES EST INFERIEUR A LA TAILLE DU BUFFER
        /* final buffer... */
        for (i = 0; i < framesLeft; i++)
        {
            *wptr++ = *rptr++; /* left */
            if (NUM_CHANNELS == 2)
                *wptr++ = *rptr++; /* right */
        }
        for (; i < framesPerBuffer; i++)
        {                // ON COMPLETE AVEC DU VIDE
            *wptr++ = 0; /* left */
            if (NUM_CHANNELS == 2)
                *wptr++ = 0; /* right */
        }
        data->frameIndex += framesLeft;
        finished = paComplete;
    }
    else
    { //IL RESTE PLUS DE FRAMES QUE LA TAILLE DU BUFFER OUTPUT
        for (i = 0; i < framesPerBuffer; i++)
        {                      //ON ECRIT TOUTE LES FRAMES DANS LE BUFFER DE SORITES
            *wptr++ = *rptr++; /* left */
            if (NUM_CHANNELS == 2)
                *wptr++ = *rptr++; /* right */
        }
        data->frameIndex += framesPerBuffer;
        finished = paContinue;
    }
    return finished;
}

/*******************************************************************/
int main(void);
int main(void)
{
    Audio audio;
    PaError err = paNoError;
    paTestData data;
    int i;
    int totalFrames;
    int numSamples;
    int numBytes;
    SAMPLE max, val;
    double average;

    printf("patest_record.c\n");
    fflush(stdout);

    data.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
    data.frameIndex = 0;
    numSamples = totalFrames * NUM_CHANNELS;
    numBytes = numSamples * sizeof(SAMPLE);
    data.recordedSamples = (SAMPLE *)malloc(numBytes); /* From now on, recordedSamples is initialised. */

    if (data.recordedSamples == NULL)
    {
        printf("Could not allocate record array.\n");
        return 84;
    }
    for (i = 0; i < numSamples; i++)
        data.recordedSamples[i] = 0;

    audio.OpenInputStream(recordCallback, &data);
    audio.StartRecording();

    printf("\n=== Now recording!! Please speak into the microphone. ===\n");
    fflush(stdout);

    while ((err = Pa_IsStreamActive(audio.stream)) == 1)
    {
        Pa_Sleep(1000);
        printf("index = %d\n", data.frameIndex);
        fflush(stdout);
    }
    if (err < 0)
        return 84;

    audio.Close();
    //     /* Write recorded data to a file. */
    // #if WRITE_TO_FILE
    //     {
    //         FILE *fid;
    //         fid = fopen("recorded.raw", "wb");
    //         if (fid == NULL)
    //         {
    //             printf("Could not open file.");
    //         }
    //         else
    //         {
    //             fwrite(data.recordedSamples, NUM_CHANNELS * sizeof(SAMPLE), totalFrames, fid);
    //             fclose(fid);
    //             printf("Wrote data to 'recorded.raw'\n");
    //         }
    //     }
    // #endif

    /* Playback recorded data.  -------------------------------------------- */
    data.frameIndex = 0;

    printf("\n=== Now playing back. ===\n");
    fflush(stdout);

    audio.OpenOutputStream(playCallback, &data);

    if (audio.stream)
    {
        audio.StartPlaying();

        printf("Waiting for playback to finish.\n");
        fflush(stdout);

        while ((err = Pa_IsStreamActive(audio.stream)) == 1)
            Pa_Sleep(100);
        if (err < 0)
            return 84;

        audio.Close();

        printf("Done.\n");
        fflush(stdout);
    }
    if (data.recordedSamples) /* Sure it is NULL or valid. */
        free(data.recordedSamples);
    return err;
}
