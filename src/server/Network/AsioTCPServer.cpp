/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPServer
*/

#include "babel.hpp"
#include "AsioTCPServer.hpp"
#include <cstring>

using namespace Babel::Server::Network;

AsioTCPServer::AsioTCPServer(int port)
:   _ioContext(),
    _acceptor(_ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    std::cout << "Server running on port : " << port << std::endl;
    startAccept();
}

AsioTCPServer::~AsioTCPServer()
{
}

void AsioTCPServer::startAccept()
{
    std::shared_ptr<AsioTCPCli> cli = std::make_shared<AsioTCPCli>(_ioContext);

    _clientsList.push_back(cli);
    _acceptor.async_accept(_clientsList.back()->getSocket(), [&] (asio::error_code err) {
        if (!err) {
            std::cout << "New Client : " << _clientsList.back()->getIpString() << std::endl;
            _clientsList.back()->read();
            _clientsList.back()->write(Babel::Res::CONNECTION_ACCEPTED, _clientsList.back()->getIpString().c_str());
        } else {
            std::cerr << "Error : " << err.message() << std::endl;
        }
        startAccept();
    });
}

void AsioTCPServer::run()
{
    _ioContext.run();
}

AsioTCPCli *AsioTCPServer::isUserLogged(const std::string &username) const
{
    for (auto it = _clientsList.cbegin(); it != _clientsList.cend(); ++it) {
        if (it->get()->getConnectedUser() && it->get()->getConnectedUser()->_name == username)
            return it->get();
    }
    return nullptr;
}

void AsioTCPServer::disconnectClient(void)
{
    for (auto it = _clientsList.cbegin(); it != _clientsList.cend(); ++it) {
        if (!it->get()->getSocket().is_open()) {
            _clientsList.erase(it);
            return;
        }
    }
}

std::shared_ptr<Call> AsioTCPServer::getUserCall(const std::string &username)
{
    for (int i = 0; i < _calls.size(); i++) {
        for (auto it = _calls[i].users.begin(); it != _calls[i].users.end(); ++it) {
            if (it->_name == username) {
                return std::make_shared<Call>(_calls[i]);
            }
        }
    }
    return nullptr;
}

std::vector<Call> &AsioTCPServer::getCalls()
{
    return _calls;
}

std::shared_ptr<Call> AsioTCPServer::isUserRequested(const std::string &username) const
{
    for (int i = 0; i < _calls.size(); i++) {
        for (auto it = _calls[i].users_requested.begin(); it != _calls[i].users_requested.end(); ++it) {
            if (it->_name == username)
                return std::make_shared<Call>(_calls[i]);
        }
    }
    return nullptr;
}

void AsioTCPServer::addCall(Call &call)
{
    _calls.push_back(call);
}