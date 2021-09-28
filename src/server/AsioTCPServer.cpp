/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPServer
*/

#include "AsioTCPServer.hpp"
#include "AsioTCPCli.hpp"

AsioTCPServer::AsioTCPServer()
:   _io_context(),
    _acceptor(_io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 9999))
{
    startAccept();
}

void AsioTCPServer::startAccept()
{
    std::shared_ptr<AsioTCPCli> cli = std::make_shared<AsioTCPCli>(_io_context);

    _cli_list.push_back(cli);
    _acceptor.async_accept(_cli_list.back()->getSocket(), [&] (asio::error_code err) {
        if (!err)
            std::cout << "New Client : " << _cli_list.back()->get_ip_string() << std::endl;
        else {
            std::cerr << "there was an error" << std::endl;
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
