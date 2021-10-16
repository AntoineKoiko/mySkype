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

class ITCPServer {
    public:
        virtual ~ITCPServer() = default;

        virtual void run() = 0;
        virtual void disconnectClient(void) = 0;

    protected:
    private:
        virtual void startAccept() = 0;

        std::deque<std::shared_ptr<ITCPCli>> _clientsList;
};

#endif /* !ITCPSERVER_HPP_ */
