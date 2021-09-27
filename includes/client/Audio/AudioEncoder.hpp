/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioEncoder
*/

#ifndef AUDIOENCODER_HPP_
#define AUDIOENCODER_HPP_

#include "opus.h"
#include "Audio.hpp"
#include "SoundEncoded.hpp"
#include "SoundFrameBuffer.hpp"

namespace Babel::Client::Audio
{
    class AudioEncoder {
        public:
            AudioEncoder();
            ~AudioEncoder();

            SoundEncoded encodeAudio(const Audio::SoundFrameBuffer &buffer);

        protected:
        private:
            OpusEncoder *_encoder;
    };
}

#endif /* !AUDIOENCODER_HPP_ */
