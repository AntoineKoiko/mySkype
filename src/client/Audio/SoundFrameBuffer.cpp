/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** SoundFrameBuffer
*/

#include "SoundFrameBuffer.hpp"

using namespace Babel::Client::Audio;

SoundFrameBuffer::SoundFrameBuffer()
{
    this->frames.fill(0);
}

SoundFrameBuffer::~SoundFrameBuffer()
{
}
