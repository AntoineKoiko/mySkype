/*
** EPITECH PROJECT, 2021
** babel
** File description:
** commands
*/

#include "AsioTCPCli.hpp"
#include "Database/UserHandler.hpp"
#include "babel.hpp"

using namespace Babel;

int AsioTCPCli::login(const std::string &username)
{
    auto serv = get_server();
    auto userHandler = serv->getUserHandler();
    User user = userHandler.getUser(username);

    if (user._exists) {
        write(201, username.c_str());
    } else {
        write(404, username.c_str());
    }
    return 0;
}