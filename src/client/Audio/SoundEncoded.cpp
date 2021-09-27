/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** SoundEncoded
*/

#include "SoundEncoded.hpp"

using namespace Babel::Client::Audio;

SoundEncoded::SoundEncoded()
{
    this->encodedSound.resize(Audio::BufferSize);
    std::fill(this->encodedSound.begin(), this->encodedSound.end(), 0);
    this->size = 0;
}

SoundEncoded::~SoundEncoded()
{
}
