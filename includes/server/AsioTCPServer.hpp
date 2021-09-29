/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPServer
*/

#ifndef ASIOTCPSERVER_HPP_
#define ASIOTCPSERVER_HPP_

#include <asio.hpp>
#include <iostream>
#include <algorithm>
#include <memory>
#include <deque>
#include "babel.hpp"
#include "AsioTCPCli.hpp"

class AsioTCPServer {
    public:
        AsioTCPServer();
        ~AsioTCPServer();

        asio::ip::tcp::socket &getSocket() const;
        void startAccept();
        void run();

    protected:
    private:
        asio::io_context _io_context;
        asio::ip::tcp::acceptor _acceptor;
        std::deque<std::shared_ptr<AsioTCPCli>> _cli_list;
};

#endif /* !ASIOTCPSERVER_HPP_ */
