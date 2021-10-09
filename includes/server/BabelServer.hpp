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
#include "DatabaseManager.hpp"
#include "UserHandler.hpp"
#include "ContactHandler.hpp"

namespace Babel::Server
{
    const int defaultPort = 9999;
    const int successCode = 0;
    const int errorCode = 84;

    class BabelServer {
        public:
            BabelServer(int port = 9999);
            ~BabelServer();

            void start();

            // Getters

            AsioTCPServer &getServer();
            const std::shared_ptr<Db::DatabaseManager> getDb() const;
            const Db::UserHandler &getUserHandler() const;
            const Db::ContactHandler &getContactHandler() const;

        protected:
        private:
            AsioTCPServer _tcpServer;
            std::shared_ptr<Db::DatabaseManager> _db;
            Db::UserHandler _userHandler;
            Db::ContactHandler _contactHandler;

    };
} // namespace babel


#endif /* !BABELSERVER_HPP_ */
