/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioOutput
*/

#ifndef AUDIOOUTPUT_HPP_
#define AUDIOOUTPUT_HPP_

#include <iostream>
#include <queue>
#include <cstring>
#include "Audio.hpp"
#include "portaudio.h"
#include "SoundFrameBuffer.hpp"

namespace Babel::Client::Audio
{
    class AudioOutput {
        public:
            AudioOutput();
            ~AudioOutput();

            void openOutputStream();
            void startPlaying();
            void addSound(const SoundFrameBuffer &sound);
            bool isEmpty() const;
            void stopPlaying();
            void close();

        protected:
        private:
            PaStreamParameters _params;
            PaStream *_stream;
            std::queue<SoundFrameBuffer> _sound;
            bool _isPlaying;

            static int callback(const void *inputBuffer, void *outputBuffer,
                   unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
                   PaStreamCallbackFlags statusFlags, void *userData);
    };
}

#endif /* !AUDIOOUTPUT_HPP_ */
