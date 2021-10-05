/*
** EPITECH PROJECT, 2021
** babel
** File description:
** BabelServer
*/

#ifndef BABELSERVER_HPP_
#define BABELSERVER_HPP_

#include <iostream>
#include <deque>
#include "AsioTCPServer.hpp"

namespace babel
{
    class BabelServer {
        public:
            BabelServer();
            ~BabelServer();

            void start();

        protected:
        private:
            AsioTCPServer _tcp_server;
    };
} // namespace babel


#endif /* !BABELSERVER_HPP_ */
