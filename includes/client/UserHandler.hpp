/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** UserHandler
*/

#ifndef USERHANDLER_HPP_
#define USERHANDLER_HPP_

#include <memory>
#include "babel.hpp"
#include "DataPacketManager.hpp"
#include "TcpClient.hpp"

class UserHandler {
    public:
        UserHandler(const std::shared_ptr<Babel::Client::Network::TcpClient> network);
        ~UserHandler();

        void login(const std::string &loginName) noexcept;

    protected:
    private:
        std::string _loginName;
        std::shared_ptr<Babel::Client::Network::TcpClient> _network;
};

#endif /* !USERHANDLER_HPP_ */
