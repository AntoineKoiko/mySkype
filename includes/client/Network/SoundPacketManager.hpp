/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** SoundPacketManager
*/

#ifndef SOUNDPACKETMANAGER_HPP_
#define SOUNDPACKETMANAGER_HPP_

#include "Network.hpp"
#include "SoundEncoded.hpp"
#include <chrono>

class SoundPacketManager {
    public:
        static Babel::Client::Network::SoundPacket createPacket(const Babel::Client::Audio::SoundEncoded &sound);
        static std::vector<char> serialize(const Babel::Client::Network::SoundPacket &soundPacket);
        static Babel::Client::Network::SoundPacket deserialize(const std::vector<char> &packet);
};

#endif /* !SOUNDPACKETMANAGER_HPP_ */
