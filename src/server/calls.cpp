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

void sendToUser(const std::string &username, Network::AsioTCPServer &tcp, std::string &str)
{
    auto client = tcp.isUserLogged(username);

    client->write(211, str.c_str());
}

void sendToUserJoin(const std::string &username, Network::AsioTCPServer &tcp, std::string &str)
{
    auto client = tcp.isUserLogged(username);

    client->write(210, str.c_str());
}

int Network::AsioTCPCli::callInit(const std::string &args)
{
    if (!_connectedUser)
        return 1;
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
        if (!user._exists || serv->getServer().isUserRequested(token))
            continue;
        // TODO : check if user is not requested somewhere else
        call.users_requested.push_back(user);
        return_str = _connectedUser->_name + ":" + this->getIpString();
        sendToUser(token, serv->getServer(), return_str);
        s.erase(0, pos + delimiter.length());
    }
    Babel::Server::Db::User user = userHandler.getUser(token);
    if (user._exists && !serv->getServer().isUserRequested(token)) {
        call.users_requested.push_back(user);
        return_str = _connectedUser->_name + ":" + this->getIpString();
        sendToUser(token, serv->getServer(), return_str);
        std::cout << s << std::endl;
    }
    call.users.push_back(*_connectedUser);
    this->write(208, "");
    return 0;
}

int Network::AsioTCPCli::callAccept(const std::string &)
{
    if (!_connectedUser)
        return 1;
    auto serv = get_server();
    auto call = serv->getServer().isUserRequested(_connectedUser->_name);
    std::string toSend;

    toSend = _connectedUser->_name + ":" + this->getIpString();
    for (auto it = call->users.begin(); it != call->users.end(); ++it)
        sendToUserJoin(it->_name, serv->getServer(), toSend);
    for (auto it = call->users.begin(); it != call->users.end(); ++it) {
        Network::AsioTCPCli *client = serv->getServer().isUserLogged(it->_name);

        if (!client->getConnectedUser())
            continue;
        toSend = client->getConnectedUser()->_name + ":" + client->getIpString();
    }
    remove(call->users_requested.begin(), call->users_requested.end(), *_connectedUser);
    call->users.push_back(*_connectedUser);
    return 0;
}

int Network::AsioTCPCli::callReject(const std::string &)
{
    if (!_connectedUser)
        return 1;
    auto serv = get_server();
    auto call = serv->getServer().isUserRequested(_connectedUser->_name);

    remove(call->users_requested.begin(), call->users_requested.end(), *_connectedUser);
    // TODO: send reject code to others
    return 0;
}