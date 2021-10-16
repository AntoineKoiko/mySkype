/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** DataPacketManager
*/

#include "DataPacketManager.hpp"

std::vector<char> DataPacketManager::serialize(const DataPacket &dataPacket)
{
    const char *packetSerialized = reinterpret_cast<const char *>(&dataPacket);
    std::vector<char> packetContainer(packetSerialized, packetSerialized + sizeof(DataPacket));

    return packetContainer;
}

DataPacket DataPacketManager::deserialize(const std::vector<char> &packet)
{
    const DataPacket *packetDeserialized = reinterpret_cast<const DataPacket *>(packet.data());

    return *packetDeserialized;
}

DataPacket DataPacketManager::createPacket(int code, const std::string &data) noexcept
{
    DataPacket packet;

    packet.code = code;
    packet.size = data.size();
    std::memcpy(packet.data, data.c_str(), data.size());
    return packet;
}
