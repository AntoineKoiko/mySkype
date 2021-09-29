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
            SoundFrameBuffer getSound();
            bool isEmpty() const;
            void stopRecording();
            void close();

        protected:
        private:
            PaStreamParameters _params;
            PaStream *_stream;
            std::queue<SoundFrameBuffer> _sound;
            bool _isRecording;

            static int callback(const void *inputBuffer, void *outputBuffer,
                   unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
                   PaStreamCallbackFlags statusFlags, void *userData);
    };
}

#endif /* !AUDIOINPUT_HPP_ */
