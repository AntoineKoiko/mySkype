/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-bsbabel-aurelien.joncour
** File description:
** main
*/

#include <iostream>
#include "portaudio.h"

typedef struct
{
    float left_phase;
    float right_phase;
}
paTestData;
/* This routine will be called by the PortAudio engine when audio is needed.
 * It may called at interrupt level on some machines so don't do anything
 * that could mess up the system like calling malloc() or free().
*/
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    /* Cast data passed through stream to our structure. */
    paTestData *data = (paTestData*)userData;
    float *out = (float*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */

    for( i=0; i<framesPerBuffer; i++ )
    {
        out++;
        *out = data->left_phase;  /* left */
        out++;
        *out = data->right_phase;  /* right */
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        data->left_phase += 0.01f;
        /* When signal reaches top, drop back down. */
        if( data->left_phase >= 1.0f ) data->left_phase -= 2.0f;
        /* higher pitch so we can distinguish left and right. */
        data->right_phase += 0.03f;
        if( data->right_phase >= 1.0f ) data->right_phase -= 2.0f;
    }
    return 0;
}

#define SAMPLE_RATE (44100)
static paTestData data;

int main()
{
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError)
        std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    PaStream *stream;

    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream( &stream,
                                0,          /* no input channels */
                                2,          /* stereo output */
                                paFloat32,  /* 32 bit floating point output */
                                SAMPLE_RATE,
                                256,        /* frames per buffer, i.e. the number
                                                   of sample frames that PortAudio will
                                                   request from the callback. Many apps
                                                   may want to use
                                                   paFramesPerBufferUnspecified, which
                                                   tells PortAudio to pick the best,
                                                   possibly changing, buffer size.*/
                                patestCallback, /* this is your callback function */
                                &data ); /*This is a pointer that will be passed to
                                                   your callback*/
    if (err != paNoError)
        std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    err = Pa_StartStream( stream );
    if (err != paNoError)
        std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    Pa_Sleep(3 * 1000);
    err = Pa_StopStream(stream);
    if (err != paNoError)
        std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    err = Pa_CloseStream(stream);
    if (err != paNoError)
        std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;

    err = Pa_Terminate();
    if (err != paNoError)
        std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    std::cout << "END" << std::endl;
    return 0;
}
