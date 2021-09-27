/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <iostream>
#include "portaudio.h"
#define PA_SAMPLE_TYPE  paFloat32
#define FRAMES_PER_BUFFER (480)
#define SAMPLE_RATE (48000)

class AudioException : public std::runtime_error {
    public:
        AudioException(std::string what)
            : std::runtime_error(what) {}
};

class Audio {
    public:
        Audio();
        ~Audio();

        void OpenInputStream(PaStreamCallback callback, void *data);
        void OpenOutputStream(PaStreamCallback callback, void *data);

        void StartPlaying();
        void StopPlaying();

        void StartRecording();
        void StopRecording();

        void Close();

        bool IsPlaying();
        bool isRecording();

        PaStream *stream;

    protected:
    private:

        void initParameters();
        PaStreamParameters _inputParameters;
        PaStreamParameters _outputParameters;
        int _sampleRate;
        int _isPlaying;
        int _isRecording;
};

#endif /* !AUDIO_HPP_ */
