/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPServer
*/

#include "babel.hpp"
#include "AsioTCPServer.hpp"
#include <cstring>

using namespace Babel::Server;

AsioTCPServer::AsioTCPServer(int port)
:   _io_context(),
    _acceptor(_io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
{
    std::cout << "Server running on port : " << port << std::endl;
    startAccept();
}

void handle_write(asio::error_code err, UN std::size_t bytes)
{
    if (err) {
        std::cerr << "Error : " << err.message() << std::endl;
    }
}

void AsioTCPServer::startAccept()
{
    std::shared_ptr<AsioTCPCli> cli = std::make_shared<AsioTCPCli>(_io_context);

    _cli_list.push_back(cli);
    _acceptor.async_accept(_cli_list.back()->getSocket(), [&] (asio::error_code err) {
        if (!err) {
            std::cout << "New Client : " << _cli_list.back()->get_ip_string() << std::endl;
            _cli_list.back()->read();
            _cli_list.back()->write(200, _cli_list.back()->get_ip_string().c_str());
        } else {
            std::cerr << "Error : " << err.message() << std::endl;
        }
        startAccept();
    });
}

AsioTCPServer::~AsioTCPServer()
{
}

void AsioTCPServer::run()
{
    _io_context.run();
}

AsioTCPCli *AsioTCPServer::isUserLogged(const std::string &username) const
{
    for (auto it = _cli_list.cbegin(); it != _cli_list.cend(); ++it) {
        if (it->get()->getConnectedUser() && it->get()->getConnectedUser()->_name == username)
            return it->get();
    }
    return nullptr;
}

void AsioTCPServer::disconnectClient(void)
{
    for (auto it = _cli_list.cbegin(); it != _cli_list.cend(); ++it) {
        if (!it->get()->getSocket().is_open()) {
            _cli_list.erase(it);
            return;
        }
    }
}