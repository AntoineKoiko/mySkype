/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** IAudioEncoder
*/

#ifndef IAUDIOENCODER_HPP_
#define IAUDIOENCODER_HPP_

#include "Audio.hpp"
#include "SoundEncoded.hpp"
#include "SoundFrameBuffer.hpp"

namespace Babel::Client::Audio
{
    class IAudioEncoder
    {
    public:
        virtual ~IAudioEncoder() = default;

        virtual SoundEncoded encodeAudio(const Audio::SoundFrameBuffer &buffer) const = 0;
    };
}

#endif /* !IAUDIOENCODER_HPP_ */
