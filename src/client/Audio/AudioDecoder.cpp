/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioDecoder
*/

#include "AudioDecoder.hpp"

using namespace Babel::Client::Audio;

AudioDecoder::AudioDecoder()
{
    int err;
    this->_decoder = opus_decoder_create(Audio::SamplingRate, Audio::NumberOfChannels, &err);

    if (err != OPUS_OK) {
        //TODO THROW ERROR:
    }
}

AudioDecoder::~AudioDecoder()
{
    if (this->_decoder) {
        opus_decoder_destroy(this->_decoder);
    }
}

SoundFrameBuffer AudioDecoder::decodeAudio(const SoundEncoded &encoded) const
{
    SoundFrameBuffer soundbuffer;
    int nbBytesDecoded = 0;

    nbBytesDecoded = opus_decode_float(this->_decoder, encoded.encodedSound.data(), encoded.size,
        soundbuffer.frames.data(), Audio::FrameSize, 0);
    if (nbBytesDecoded < OPUS_OK) {
        //THROW ERROR
    }
    return soundbuffer;
}
