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
#include "call.hpp"
#include "ITCPServer.hpp"

namespace Babel::Server::Network
{
    class AsioTCPServer : public ITCPServer {
        public:
            AsioTCPServer(int port = 9999);
            ~AsioTCPServer();

            asio::ip::tcp::socket &getSocket() const;
            std::vector<Call> &getCalls();
            AsioTCPCli *isUserLogged(const std::string &) const;
            Call *isUserRequested(const std::string &);
            Call *getUserCall(const std::string &);
            void addCall(Call &);
            void run();
            void disconnectClient(void);

        protected:
        private:
            void startAccept();

            asio::io_context _ioContext;
            asio::ip::tcp::acceptor _acceptor;
            std::deque<std::shared_ptr<AsioTCPCli>> _clientsList;
            std::vector<Call> _calls;
    };
}

#endif /* !ASIOTCPSERVER_HPP_ */
