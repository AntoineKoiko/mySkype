/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <vector>

namespace Babel::Client::Network
{
    const int magicNumber = 4269;

    struct SoundPacket
    {
        int magicNumber;
        std::vector<unsigned char> soundPayload;
        unsigned long int timestamp;
    };
}

#endif /* !NETWORK_HPP_ */
