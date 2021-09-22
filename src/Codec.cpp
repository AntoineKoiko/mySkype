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


unsigned char *Codec::encodeAudio(float *input)
{
    unsigned char *output = (unsigned char *) malloc(sizeof(unsigned char) * MAX_DATA_BYTES);
    int return_value = 0;

    memset(output, 0, MAX_DATA_BYTES * sizeof(unsigned char));
    std::cout << "PRE ENCODE" << std::endl;
    return_value = opus_encode_float(_encoder, input, FRAME_SIZE, output, MAX_DATA_BYTES);
    std::cout << "POST ENCODE" << std::endl;
    std::cout << "RV = " << return_value << std::endl;
    for (size_t i = 0; i < MAX_DATA_BYTES * 2; i += 2) {
        std::cout << "OUTPUT -> " << (int) output[i] << " - " << (int) output[i + 1] << std::endl;
    }
    return output;
}

void Codec::createDecoder()
{
    _decoder = opus_decoder_create(SAMPLING_RATE, NUMBER_OF_CHANNELS, &_opusError);
}

void Codec::destroyDecoder()
{
    opus_decoder_destroy(_decoder);
}

void Codec::decodeAudio(unsigned char *output, float **input)
{
/*    free(*input);
    *input = (float *) malloc(sizeof(float) * FRAME_SIZE * NUMBER_OF_CHANNELS);
    std::cout << "PRE DECODE" << std::endl;
    int opus_decode_float(_decoder, output, MAX_DATA_BYTES, *input, FRAME_SIZE, DECODE_FEC);
    std::cout << "POST DECODE" << std::endl;
*/
    free(output);
}