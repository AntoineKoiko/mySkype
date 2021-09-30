/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioEncoder
*/

#include "AudioEncoder.hpp"

using namespace Babel::Client::Audio;

AudioEncoder::AudioEncoder() : _encoder(nullptr)
{
    int err;

    this->_encoder = opus_encoder_create(Audio::SamplingRate, Audio::NumberOfChannels, OPUS_APPLICATION_VOIP, &err);
    if (err != OPUS_OK) {
        throw EncoderError("Creation of the encoder failed !");
    }
}

AudioEncoder::~AudioEncoder()
{
    if (this->_encoder) {
        opus_encoder_destroy(this->_encoder);
    }
}

SoundEncoded AudioEncoder::encodeAudio(const Audio::SoundFrameBuffer &buffer) const
{
    Audio::SoundEncoded encoded;
    int nbBytesEncoded = 0;

    nbBytesEncoded = opus_encode_float(this->_encoder, buffer.frames.data(), Audio::FrameSize, encoded.encodedSound.data(), Audio::BufferSize);
    if (nbBytesEncoded < OPUS_OK) {
        throw DecoderError("Encoding failed !");
    }
    encoded.size = nbBytesEncoded;
    encoded.encodedSound.resize(nbBytesEncoded);
    return encoded;
}
