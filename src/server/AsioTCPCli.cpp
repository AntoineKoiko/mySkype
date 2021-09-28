/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPCli
*/

#include "AsioTCPCli.hpp"
#include <iostream>

AsioTCPCli::AsioTCPCli(asio::io_context &context)
: _socket(context)
{
}

AsioTCPCli::~AsioTCPCli()
{
    std::cout << "ptdr" << std::endl;
}

asio::ip::tcp::socket &AsioTCPCli::getSocket()
{
    return _socket;
}

std::string AsioTCPCli::get_ip_string() const
{
    return _socket.remote_endpoint().address().to_string();
}