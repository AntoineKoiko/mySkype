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

int sendToUser(const std::string &username, Network::AsioTCPServer &tcp, std::string &str)
{
    auto client = tcp.isUserLogged(username);

    if (client) {
        client->write(Babel::Res::CALL_REQUEST, str.c_str());
        return 0;
    }
    return 1;
}

int sendToUserJoin(const std::string &username, Network::AsioTCPServer &tcp, std::string &str)
{
    auto client = tcp.isUserLogged(username);

    if (client) {
        client->write(Babel::Res::JOIN_CALL, str.c_str());
        return 0;
    }
    return 1;
}

int Network::AsioTCPCli::callInit(const std::string &args)
{
    if (!_connectedUser)
        return 1;
    auto serv = get_server();
    auto userHandler = serv->getUserHandler();
    std::vector<Db::User> users_list;
    std::string s(args);
    std::string return_str;
    Call call;
    std::vector<std::string> argumentList;

    if (serv->getServer().getUserCall(_connectedUser->_name))
        return -1;
    argumentList = splitString(s, ";");
    for (const auto &argument : argumentList) {
        Babel::Server::Db::User user = userHandler.getUser(argument);
        if (!user._exists || serv->getServer().isUserRequested(argument) || serv->getServer().getUserCall(argument))
            continue;
        call.users_requested.push_back(user);
        return_str = _connectedUser->_name + ":" + this->getIpString();
        if (sendToUser(argument, serv->getServer(), return_str)) {
            // remove(call.users_requested.begin(), call.users_requested.end(), user);
        }
    }
    call.users.push_back(*_connectedUser);
    serv->getServer().addCall(call);
    this->write(Babel::Res::CALL_TAKEN, "");
    return 0;
}

int Network::AsioTCPCli::callAccept(const std::string &)
{
    if (!_connectedUser)
        return 1;
    auto serv = get_server();
    auto call = serv->getServer().isUserRequested(_connectedUser->_name);

    if (call == nullptr) {
        return 1;
    }
    std::string toSend = _connectedUser->_name + ":" + this->getIpString();
    for (auto it = call->users.begin(); it != call->users.end(); ++it) {
        sendToUserJoin(it->_name, serv->getServer(), toSend); //Send new people on call notification
    }
    toSend.clear();
    for (auto it = call->users.begin(); it != call->users.end(); ++it) {
        Network::AsioTCPCli *client = serv->getServer().isUserLogged(it->_name);

        if (toSend.length() > 0)
            toSend += ";";
        if (client && !client->getConnectedUser())
            continue;
        toSend += client->getConnectedUser()->_name + ":" + client->getIpString();
    }
    remove(call->users_requested.begin(), call->users_requested.end(), *_connectedUser);
    call->users.push_back(*_connectedUser);
    this->write(Babel::Res::CALL_ACCEPTED, toSend.c_str());
    return 0;
}

int Network::AsioTCPCli::callReject(const std::string &)
{
    if (!_connectedUser)
        return 1;
    auto serv = get_server();
    auto call = serv->getServer().isUserRequested(_connectedUser->_name);

    remove(call->users_requested.begin(), call->users_requested.end(), *_connectedUser);
    return 0;
}

int Network::AsioTCPCli::callHangup(const std::string &)
{
    //TODO : retirer le user de tous les calls
    auto serv = get_server();
    auto call = serv->getServer().getUserCall(_connectedUser->_name);

    // remove(call->users.begin(), call->users.end(), _connectedUser);
    this->write(213, "");
}