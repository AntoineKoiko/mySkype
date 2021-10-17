/*
** EPITECH PROJECT, 2021
** babel
** File description:
** ITCPServer
*/

#ifndef ITCPSERVER_HPP_
#define ITCPSERVER_HPP_

#include <deque>
#include <memory>
#include "ITCPCli.hpp"

namespace Babel::Server::Network
{
    class ITCPServer {
        public:
            virtual ~ITCPServer() = default;

            virtual std::vector<Call> &getCalls() = 0;
            virtual AsioTCPCli *isUserLogged(const std::string &) const = 0;
            virtual Call *isUserRequested(const std::string &) = 0;
            virtual Call *getUserCall(const std::string &) = 0;
            virtual void addCall(Call &) = 0;
            virtual void run() = 0;
            virtual void disconnectClient(void) = 0;

        protected:
        private:
            virtual void startAccept() = 0;
    };
}

#endif /* !ITCPSERVER_HPP_ */
