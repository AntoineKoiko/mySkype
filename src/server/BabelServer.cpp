/*
** EPITECH PROJECT, 2021
** babel
** File description:
** BabelServer
*/

#include "BabelServer.hpp"

using namespace Babel::Server;

BabelServer::BabelServer(int port) : _tcpServer(port), _db(std::make_shared<Db::DatabaseManager>("babel.db")), _userHandler(_db), _contactHandler(_db)
{
}

BabelServer::~BabelServer()
{
}

void BabelServer::start()
{
    _tcpServer.run();
}

const std::shared_ptr<Db::DatabaseManager> BabelServer::getDb() const
{
    return _db;
}

const Db::UserHandler &BabelServer::getUserHandler() const
{
    return _userHandler;
}

const Db::ContactHandler &BabelServer::getContactHandler() const
{
    return _contactHandler;
}

Network::AsioTCPServer &BabelServer::getServer()
{
    return _tcpServer;
}