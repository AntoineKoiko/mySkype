/*
** EPITECH PROJECT, 2021
** babel
** File description:
** BabelServer
*/

#include "BabelServer.hpp"

using namespace Babel::Server;

BabelServer::BabelServer(int port) : _tcpServer(port), _db(std::make_shared<DatabaseManager>("babel.db")), _userHandler(_db), _contactHandler(_db)
{
}

BabelServer::~BabelServer()
{
}

void BabelServer::start()
{
    _tcpServer.run();
}

const std::shared_ptr<DatabaseManager> BabelServer::getDb() const
{
    return _db;
}

const UserHandler &BabelServer::getUserHandler() const
{
    return _userHandler;
}

const ContactHandler &BabelServer::getContactHandler() const
{
    return _contactHandler;
}

AsioTCPServer &BabelServer::getServer()
{
    return _tcpServer;
}