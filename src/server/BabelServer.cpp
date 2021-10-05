/*
** EPITECH PROJECT, 2021
** babel
** File description:
** BabelServer
*/

#include "BabelServer.hpp"

using namespace babel;

BabelServer::BabelServer() : _tcp_server()
{
}

BabelServer::~BabelServer()
{
}

void BabelServer::start()
{
    _tcp_server.run();
}
