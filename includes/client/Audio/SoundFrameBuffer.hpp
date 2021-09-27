/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** SoundFrameBuffer
*/

#ifndef SOUNDFRAMEBUFFER_HPP_
#define SOUNDFRAMEBUFFER_HPP_

#include <array>
#include "Audio.hpp"

namespace Babel::Client::Audio
{
    class SoundFrameBuffer {
        public:
            SoundFrameBuffer();
            ~SoundFrameBuffer();

            std::array<float, Audio::BufferSize> frames;

        protected:
        private:
    };
}



#endif /* !SOUNDFRAMEBUFFER_HPP_ */
