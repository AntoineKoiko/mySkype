/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** DataPacketManager
*/

#ifndef DATAPACKETMANAGER_HPP_
#define DATAPACKETMANAGER_HPP_

#include "babel.hpp"

class DataPacketManager {
    public:
        static std::vector<char> serialize(const DataPacket &dataPacket);
        static DataPacket deserialize(const std::vector<char> &packet);

    protected:
    private:
};

#endif /* !DATAPACKETMANAGER_HPP_ */
