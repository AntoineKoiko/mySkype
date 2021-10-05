/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** User Handler
*/

#include "../../../includes/server/Database/UserHandler.hpp"

using namespace Babel;

UserHandler::UserHandler(DatabaseManager &dbManager) : _dbManager(dbManager)
{
    std::vector<std::pair<const std::string, const std::string>> userDescription =
    {{"pseudo", "text"}};

    if (!(_dbManager.checkIfTableExist(USER_TABLE_NAME))) {
        _dbManager.createTable(USER_TABLE_NAME, USER_PRIMARY_KEY_NAME, userDescription);
    }
}

UserHandler::~UserHandler() {}

void UserHandler::addUser(const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string>> newUser
    = {{"int", std::to_string(_dbManager.getNextFreePrimaryKey(USER_TABLE_NAME, USER_PRIMARY_KEY_NAME))},
    {"text", name}};

    _dbManager.addEntry(USER_TABLE_NAME, newUser);
}

void UserHandler::removeUser(const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> userSearched
    = {{"pseudo", "text", name}};

    _dbManager.deleteEntry(USER_TABLE_NAME, userSearched);
}

User UserHandler::getUser(const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> userSearched
    = {{"pseudo", "text", name}};
    std::vector<std::vector<std::string>> userTable =
    _dbManager.getEntry(USER_TABLE_NAME, userSearched);
    User user;

    if (userTable.size() > 0)
        user._name = userTable[0][1];
    return user;
}