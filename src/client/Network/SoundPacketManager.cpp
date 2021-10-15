/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** SoundPacketManager
*/

#include "SoundPacketManager.hpp"
#include <cstring>

Babel::Client::Network::SoundPacket SoundPacketManager::createPacket(const Babel::Client::Audio::SoundEncoded &sound)
{
    Babel::Client::Network::SoundPacket packet;

    packet.magicNumber = Babel::Client::Network::magicNumber;
    packet.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    packet.payloadSize = sound.size;
    std::memcpy(packet.soundPayload, sound.encodedSound.data(), sound.size);

    return packet;
}

std::vector<char> SoundPacketManager::serialize(const Babel::Client::Network::SoundPacket &soundPacket)
{
    const char *packetSerialized = reinterpret_cast<const char*>(&soundPacket);
    std::vector<char> packetContainer(packetSerialized, packetSerialized + sizeof(Babel::Client::Network::SoundPacket));

    return packetContainer;
}

Babel::Client::Network::SoundPacket SoundPacketManager::deserialize(const std::vector<char> packet)
{
    const Babel::Client::Network::SoundPacket *packetDeserialized = reinterpret_cast<const Babel::Client::Network::SoundPacket *>(packet.data());

    return *packetDeserialized;
}