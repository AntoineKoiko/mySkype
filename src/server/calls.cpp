/*
** EPITECH PROJECT, 2021
** babel
** File description:
** calls
*/


#include "BabelServer.hpp"
#include "Network/AsioTCPCli.hpp"
#include "Network/AsioTCPServer.hpp"
#include "utils.hpp"
#include "call.hpp"
#include "Database/UserHandler.hpp"
#include "Database/User.hpp"
#include <vector>

using namespace Babel::Server;

// TODO: if user initiating the call is already in a call --> abort

void sendToUser(const std::string &username, Network::AsioTCPServer &tcp, std::string &str)
{
    auto client = tcp.isUserLogged(username);

    client->write(211, str.c_str());
}

int Network::AsioTCPCli::callInit(const std::string &args)
{
    auto serv = get_server();
    auto userHandler = serv->getUserHandler();
    std::vector<Db::User> users_list;
    std::size_t pos = 0;
    std::string token;
    std::string s = args;
    std::string delimiter = ";";
    std::string return_str;
    Call call;

    if (serv->getServer().getUserCall(_connectedUser->_name))
        return -1;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        Babel::Server::Db::User user = userHandler.getUser(token);
        if (!user._exists) {
            continue;
        }
        call.users_requested.push_back(user);
        return_str = _connectedUser->_name + ":" + this->getIpString();
        sendToUser(token, serv->getServer(), return_str);
        s.erase(0, pos + delimiter.length());
    }
    Babel::Server::Db::User user = userHandler.getUser(token);
    if (!user._exists) {
        return 0;
    }
    call.users_requested.push_back(user);
    return_str = _connectedUser->_name + ":" + this->getIpString();
    sendToUser(token, serv->getServer(), return_str);
    std::cout << s << std::endl;
    this->write(208, "");
    return 0;
}