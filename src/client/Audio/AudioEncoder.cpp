/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AudioEncoder
*/

// #include "client/Audio/AudioEncoder.hpp"
#include "AudioEncoder.hpp"

using namespace Babel::Client::Audio;

AudioEncoder::AudioEncoder() : _encoder(nullptr)
{
    int err;

    this->_encoder = opus_encoder_create(Audio::SamplingRate, Audio::NumberOfChannels, OPUS_APPLICATION_VOIP, &err);
    if (err != OPUS_OK) {
        //TODO THROW ERROR;
    }
}

AudioEncoder::~AudioEncoder()
{
    if (this->_encoder) {
        opus_encoder_destroy(this->_encoder);
    }
}
#include <iostream>
SoundEncoded AudioEncoder::encodeAudio(const Audio::SoundFrameBuffer &buffer)
{
    Audio::SoundEncoded encoded;
    int nbBytesEncoded = 0;

    nbBytesEncoded = opus_encode_float(this->_encoder, buffer.frames.data(), Audio::FrameSize, encoded.encodedSound.data(), Audio::BufferSize);
    if (nbBytesEncoded < OPUS_OK) {
        //TODO THROW ERROR
    }
    encoded.size = nbBytesEncoded;
    encoded.encodedSound.resize(nbBytesEncoded);
    std::cout << "DEBUG: nbBytesEncoded: " << nbBytesEncoded << "BufferSize: " << encoded.encodedSound.size() << std::endl;
    return encoded;
}
