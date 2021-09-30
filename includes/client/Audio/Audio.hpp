/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include "AudioError.hpp"

namespace Babel::Client::Audio {
    const int FrameSize = 480;
    const int NumberOfChannels = 2;
    const int SamplingRate = 48000;
    const int BufferSize = FrameSize * NumberOfChannels;
}

#endif /* !AUDIO_HPP_ */
