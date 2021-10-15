/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** IAudioInput
*/

#ifndef IAUDIOINPUT_HPP_
#define IAUDIOINPUT_HPP_

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include "ICallHandler.hpp"
#include "Audio.hpp"
#include "portaudio.h"
#include "SoundFrameBuffer.hpp"

namespace Babel::Client::Audio
{
    class IAudioInput {
        public:
            virtual ~IAudioInput() = default;

            virtual void openInputStream() = 0;
            virtual void close() = 0;

            virtual void startRecording() = 0;
            virtual void stopRecording() = 0;

            virtual SoundFrameBuffer getSound() = 0;

            virtual bool isEmpty() const = 0;

            virtual void info() = 0;
    };
}

#endif /* !IAUDIOINPUT_HPP_ */
