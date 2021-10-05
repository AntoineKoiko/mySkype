/*
** EPITECH PROJECT, 2021
** babel
** File description:
** BabelServer
*/

#include "BabelServer.hpp"

using namespace Babel;

BabelServer::BabelServer() : _tcp_server(), _db("babel")
{
}

BabelServer::~BabelServer()
{
}

void BabelServer::start()
{
    _tcp_server.run();
}
