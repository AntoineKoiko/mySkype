/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioInput
*/

#ifndef AUDIOINPUT_HPP_
#define AUDIOINPUT_HPP_

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include "Audio.hpp"
#include "portaudio.h"
#include "SoundFrameBuffer.hpp"

namespace Babel::Client::Audio
{
    class AudioInput {
        public:
            AudioInput();
            ~AudioInput();

            void openInputStream();
            void startRecording();
            void stopRecording();
            void close();

            std::queue<SoundFrameBuffer> _sound;
            PaStream *_stream;

        protected:
        private:
            PaStreamParameters _params;
            bool _isRecording;

            static int callback(const void *inputBuffer, void *outputBuffer,
                   unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
                   PaStreamCallbackFlags statusFlags, void *userData);
    };
}

#endif /* !AUDIOINPUT_HPP_ */
