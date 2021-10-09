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
#include <memory>
#include "AsioTCPServer.hpp"
#include "Database/DatabaseManager.hpp"
#include "Database/UserHandler.hpp"
#include "Database/ContactHandler.hpp"

namespace Babel::Server
{
    class BabelServer {
        public:
            BabelServer(int port = 9999);
            ~BabelServer();

            void start();

            // Getters

            AsioTCPServer &getServer();
            const std::shared_ptr<DatabaseManager> getDb() const;
            const UserHandler &getUserHandler() const;
            const ContactHandler &getContactHandler() const;

        protected:
        private:
            AsioTCPServer _tcpServer;
            std::shared_ptr<DatabaseManager> _db;
            UserHandler _userHandler;
            ContactHandler _contactHandler;

    };
} // namespace babel


#endif /* !BABELSERVER_HPP_ */
