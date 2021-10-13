/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** IAudioOutput
*/

#ifndef IAUDIOOUTPUT_HPP_
#define IAUDIOOUTPUT_HPP_

#include <iostream>
#include <queue>
#include <cstring>
#include "Audio.hpp"
#include "portaudio.h"
#include "SoundFrameBuffer.hpp"

namespace Babel::Client::Audio
{
    class IAudioOutput {
        public:
            virtual ~IAudioOutput() = default;

            virtual void openOutputStream() = 0;
            virtual void close() = 0;

            virtual void startPlaying() = 0;
            virtual void stopPlaying() = 0;

            virtual void addSound(const SoundFrameBuffer &sound) = 0;
            
            virtual bool isEmpty() const = 0;
    };
}

#endif /* !IAUDIOOUTPUT_HPP_ */
