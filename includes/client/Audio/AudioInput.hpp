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
#include "ICallHandler.hpp"
#include "Audio.hpp"
#include "portaudio.h"
#include "SoundFrameBuffer.hpp"
#include "IAudioInput.hpp"

namespace Babel::Client::Audio
{
    class AudioInput : public IAudioInput {
        public:
            AudioInput(ICallHandler *callHandler);
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
            ICallHandler *_callHandler;
            bool _isRecording;

            static int callback(const void *inputBuffer, void *outputBuffer,
                   unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
                   PaStreamCallbackFlags statusFlags, void *userData);
    };
}

#endif /* !AUDIOINPUT_HPP_ */
