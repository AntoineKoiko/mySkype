/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** User Handler
*/

#include "UserHandler.hpp"

using namespace Babel::Server::Db;

UserHandler::UserHandler(const std::shared_ptr<DatabaseManager> dbManager) : _dbManager(dbManager)
{
    std::vector<std::pair<const std::string, const std::string>> userDescription =
    {{"pseudo", "text"}};
    std::vector<std::pair<const std::string, const std::string>> userConnectedDescription =
    {{"pseudo", "text"}};

    if (!(_dbManager->checkIfTableExist(USER_TABLE_NAME))) {
        _dbManager->createTable(USER_TABLE_NAME, USER_PRIMARY_KEY_NAME, userDescription);
    }
    if (!(_dbManager->checkIfTableExist(USER_CONNECTED_TABLE_NAME))) {
        _dbManager->createTable(USER_CONNECTED_TABLE_NAME, USER_PRIMARY_KEY_NAME, userConnectedDescription);
    }
}

UserHandler::~UserHandler() {}

void UserHandler::addUser(const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string>> newUser
    = {{"int", std::to_string(_dbManager->getNextFreePrimaryKey(USER_TABLE_NAME, USER_PRIMARY_KEY_NAME))},
    {"text", name}};

    _dbManager->addEntry(USER_TABLE_NAME, newUser);
}

void UserHandler::removeUser(const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> userSearched
    = {{"pseudo", "text", name}};

    _dbManager->deleteEntry(USER_TABLE_NAME, userSearched);
}

User UserHandler::getUser(const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> userSearched
    = {{"pseudo", "text", name}};
    std::vector<std::vector<std::string>> userTable =
    _dbManager->getEntry(USER_TABLE_NAME, userSearched);
    std::vector<std::vector<std::string>> userConnectedTable =
    _dbManager->getEntry(USER_CONNECTED_TABLE_NAME, userSearched);
    User user;

    if (userTable.size() > 0) {
        user._name = userTable[0][1];
        user._exists = true;
        if (userConnectedTable.size() != 0)
            user._isConnected = true;
    }
    return user;
}

void UserHandler::connectUser(const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string>> newUserConnected
    = {{"int", std::to_string(_dbManager->getNextFreePrimaryKey(USER_CONNECTED_TABLE_NAME, USER_PRIMARY_KEY_NAME))},
    {"text", name}};

    _dbManager->addEntry(USER_CONNECTED_TABLE_NAME, newUserConnected);
}

void UserHandler::disconnectUser(const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> userConnectedSearched
    = {{"pseudo", "text", name}};

    _dbManager->deleteEntry(USER_CONNECTED_TABLE_NAME, userConnectedSearched);
}