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
#include "Database/DatabaseManager.hpp"
#include "Database/UserHandler.hpp"
#include "Database/ContactHandler.hpp"

namespace Babel
{
    class BabelServer {
        public:
            BabelServer(int port = 9999);
            ~BabelServer();

            void start();

            // Getters

            const DatabaseManager &getDb() const;
            const UserHandler &getUserHandler() const;
            const ContactHandler &getContactHandler() const;

        protected:
        private:
            AsioTCPServer _tcp_server;
            DatabaseManager _db;
            UserHandler _userHandler;
            ContactHandler _contactHandler;

    };
} // namespace babel


#endif /* !BABELSERVER_HPP_ */
