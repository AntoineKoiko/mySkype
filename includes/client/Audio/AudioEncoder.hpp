/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioEncoder
*/

#ifndef AUDIOENCODER_HPP_
#define AUDIOENCODER_HPP_

#include "IAudioEncoder.hpp"

namespace Babel::Client::Audio
{
    class AudioEncoder : public IAudioEncoder {
        public:
            AudioEncoder();
            ~AudioEncoder();

            SoundEncoded encodeAudio(const Audio::SoundFrameBuffer &buffer) const;

        protected:
        private:
            OpusEncoder *_encoder;
    };
}

#endif /* !AUDIOENCODER_HPP_ */
