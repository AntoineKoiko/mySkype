/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** UserHandler
*/

#include "UserHandler.hpp"

UserHandler::UserHandler(const std::shared_ptr<Babel::Client::Network::TcpClient> network) : _loginName(""), _network(network)
{
}

UserHandler::~UserHandler()
{
}

void UserHandler::login(const std::string &loginName) noexcept
{
    DataPacket loginPacket;

    _loginName = loginName;
    loginPacket.magic = MAGIC_NUMBER;
    loginPacket.code = 000;
    loginPacket.size = loginName.size();
    std::memset(loginPacket.data, 0, READ_SIZE * sizeof(char));
    std::memcpy(loginPacket.data, loginName.c_str(), loginName.size());
    _network->send(DataPacketManager::serialize(loginPacket));
}
