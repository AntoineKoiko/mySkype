/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioDecoder
*/

#ifndef AUDIODECODER_HPP_
#define AUDIODECODER_HPP_

#include "IAudioDecoder.hpp"

namespace Babel::Client::Audio
{
    class AudioDecoder : public IAudioDecoder {
        public:
            AudioDecoder();
            ~AudioDecoder();

            SoundFrameBuffer decodeAudio(const SoundEncoded &encoded) const;

        protected:
        private:
            OpusDecoder *_decoder;
    };
}

#endif /* !AUDIODECODER_HPP_ */
