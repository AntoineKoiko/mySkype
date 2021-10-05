/*
** EPITECH PROJECT, 2021
** babel
** File description:
** BabelServer
*/

#include "BabelServer.hpp"

using namespace Babel;

BabelServer::BabelServer(int ac, char *av[]) : _tcp_server(), _db("babel"), _userHandler(_db), _contactHandler(_db)
{
}

BabelServer::~BabelServer()
{
}

void BabelServer::start()
{
    _tcp_server.run();
}

const DatabaseManager &BabelServer::getDb() const
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