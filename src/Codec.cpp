/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Codec
*/

#include "Codec.hpp"

Codec::Codec()
{

}

Codec::~Codec()
{

}

void Codec::createEncoder()
{
    _encoder = opus_encoder_create(SAMPLING_RATE, NUMBER_OF_CHANNELS, OPUS_APPLICATION_VOIP, &_opusError);
}

void Codec::destroyEncoder()
{
    opus_encoder_destroy(_encoder);
}


std::vector<std::pair<unsigned char[4096], int>> Codec::encodeAudio(float *input, int numSamples)
{
    std::vector<std::pair<unsigned char[4096], int>> audioEncoded = {};
    float *tmpBuff = (float *)malloc(FRAME_SIZE * NUMBER_OF_CHANNELS * sizeof(float));
    unsigned char *output = (unsigned char *) malloc(sizeof(unsigned char) * MAX_DATA_BYTES);
    int return_value = 0;
    int encoded_length = 0;
    int totalSizeEncoded = 0;

    for (int i = 0; i < numSamples; i+= FRAME_SIZE * 2) {
        std::pair<unsigned char[4096], int> p1;

        memset(tmpBuff, 0, FRAME_SIZE * NUMBER_OF_CHANNELS * sizeof(float));
        memcpy(tmpBuff, &input[i], FRAME_SIZE * NUMBER_OF_CHANNELS * sizeof(float));
        p1.second = opus_encode_float(_encoder, tmpBuff, FRAME_SIZE, p1.first, MAX_DATA_BYTES);
        std::cout << "origin: " << FRAME_SIZE * NUMBER_OF_CHANNELS * sizeof(float) << " to: " << p1.second << std::endl;
        audioEncoded.push_back(p1);
        totalSizeEncoded += p1.second;
    }
    std::cout << "Total Size Encoded: " << totalSizeEncoded << std::endl;
    return audioEncoded;
}

void Codec::createDecoder()
{
    _decoder = opus_decoder_create(SAMPLING_RATE, NUMBER_OF_CHANNELS, &_opusError);
}

void Codec::destroyDecoder()
{
    opus_decoder_destroy(_decoder);
}

void Codec::decodeAudio(std::vector<std::pair<unsigned char[4096], int>> encoded, float *decoded)
{
    int i = 0;
    int return_value = 0;

    std::cout << "Starting decoding" << std::endl;
    for (std::pair<unsigned char[4096], int> element : encoded) {
        return_value = opus_decode_float(_decoder, element.first, element.second, &decoded[i], FRAME_SIZE, DECODE_FEC);
        std::cout << "ret: " << return_value << std::endl;
        i += FRAME_SIZE * 2;
    }
}