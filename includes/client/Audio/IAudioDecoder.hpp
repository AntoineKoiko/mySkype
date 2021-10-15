/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** IAudioDecoder
*/

#ifndef IAUDIODECODER_HPP_
#define IAUDIODECODER_HPP_

#include "opus.h"
#include "Audio.hpp"
#include "SoundEncoded.hpp"
#include "SoundFrameBuffer.hpp"

namespace Babel::Client::Audio
{
    class IAudioDecoder {
        public:
            virtual ~IAudioDecoder() = default;

            virtual SoundFrameBuffer decodeAudio(const SoundEncoded &encoded) const = 0;
    };
}

#endif /* !IAUDIODECODER_HPP_ */
