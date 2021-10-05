/*
** EPITECH PROJECT, 2021
** babel
** File description:
** commands
*/

#include "AsioTCPCli.hpp"
#include "Database/UserHandler.hpp"
#include "utils.hpp"

using namespace Babel;

int AsioTCPCli::login(const std::string &username)
{
    std::cout << "Client : " << this->get_ip_string() << " trying to log in as " << username << std::endl;
    auto serv = get_server();
    auto userHandler = serv->getUserHandler();
    User user = userHandler.getUser(username);

    if (user._exists) {
        write(201, username.c_str());
        this->_connected_user = std::make_shared<User>(user);
    } else {
        write(404, username.c_str());
    }
    return 0;
}