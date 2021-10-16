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
    loginPacket = DataPacketManager::createPacket(000, loginName);
    _network->send(DataPacketManager::serialize(loginPacket));
}

void UserHandler::setIpAddr(const std::string &ipAddr) noexcept
{
    _ipAddr = ipAddr;
}

std::string UserHandler::getIpAddr() noexcept
{
    return _ipAddr;
}