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
#include "AsioTCPCli.hpp"

namespace Babel::Server
{
    class AsioTCPServer {
        public:
            AsioTCPServer(int port = 9999);
            ~AsioTCPServer();

            asio::ip::tcp::socket &getSocket() const;
            AsioTCPCli *isUserLogged(const std::string &) const;
            void run();
            void disconnectClient(void);

        protected:
        private:
            void startAccept();

            asio::io_context _ioContext;
            asio::ip::tcp::acceptor _acceptor;
            std::deque<std::shared_ptr<AsioTCPCli>> _clientsList;
    };
}

#endif /* !ASIOTCPSERVER_HPP_ */
