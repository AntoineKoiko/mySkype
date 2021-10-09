/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPCli
*/

#ifndef ASIOTCPCLI_HPP_
#define ASIOTCPCLI_HPP_

#include <asio.hpp>
#include <map>
#include "User.hpp"
#include "babel.hpp"

namespace Babel::Server::Network
{
    class AsioTCPCli : public std::enable_shared_from_this<AsioTCPCli> {

        typedef int (AsioTCPCli::*cmdFunction)(const std::string &);

        public:
            AsioTCPCli(asio::io_context &);
            ~AsioTCPCli();

            asio::ip::tcp::socket &getSocket();
            const std::string getIpString() const;
            void read();
            void write(int code, const char data[2064]);
            void handleRead(const asio::error_code &, const std::size_t);
            void handleWrite(const asio::error_code &, const std::size_t);
            const std::shared_ptr<Db::User> getConnectedUser() const;

            // cmds
            int login(const std::string &);
            int addContactRequest(const std::string &);
            int acceptContact(const std::string &);
            int denyContact(const std::string &);
            int delContact(const std::string &);
            int getContacts(const std::string &);

        protected:
        private:
            asio::ip::tcp::socket _socket;
            std::shared_ptr<Db::User> _connectedUser;
            unsigned char _buffer[2064];
            std::map<int, cmdFunction> _cmdMap;
    };
}

#endif /* !ASIOTCPCLI_HPP_ */
