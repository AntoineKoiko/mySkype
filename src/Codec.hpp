/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Codec
*/

#ifndef CODEC_HPP_
#define CODEC_HPP_

#include <iostream>
#include <cstdio>

#include <stdlib.h>
#include <string.h>

#include "opus.h"

#define SAMPLING_RATE (48000)
#define FRAME_SIZE (480)
#define NUMBER_OF_CHANNELS (2)
#define MAX_DATA_BYTES (1000)
#define DECODE_FEC (0)

class CodecException : public std::runtime_error
{
    public:
        CodecException(std::string what) : std::runtime_error(what) {}
};

class Codec
{
    public:
        Codec();
        ~Codec();

        void createEncoder();
        void destroyEncoder();

        unsigned char *encodeAudio(float *input);

        void createDecoder();
        void destroyDecoder();

        void decodeAudio(unsigned char *output, float **input);

    protected:
    
    private:
        OpusEncoder *_encoder;
        OpusDecoder *_decoder;
        int _opusError;

};

#endif /* !CODEC_HPP_ */
