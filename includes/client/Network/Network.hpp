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

#pragma pack(push, 1)
    struct SoundPacket
    {
        int magicNumber;
        unsigned char soundPayload[256];
        int payloadSize;
        unsigned long int timestamp;
    };
#pragma pack(pop)
}

#endif /* !NETWORK_HPP_ */
