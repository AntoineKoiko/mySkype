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
#include "Database/User.hpp"

class AsioTCPCli : public std::enable_shared_from_this<AsioTCPCli> {

    typedef int (AsioTCPCli::*cmd_func)(const std::string &);

    public:
        AsioTCPCli(asio::io_context &);
        ~AsioTCPCli();

        asio::ip::tcp::socket &getSocket();
        const std::string get_ip_string() const;
        void read();
        void write(int code, const char data[2048]);
        void handle_read(const asio::error_code &, const std::size_t);
        void handle_write(const asio::error_code &, const std::size_t);
        const std::shared_ptr<Babel::User> getConnectedUser() const;

        // cmds
        int login(const std::string &);

    protected:
    private:
        asio::ip::tcp::socket _socket;
        std::shared_ptr<Babel::User> _connected_user;
        unsigned char _buffer[2048];
        std::string _data_buffer;
        std::map<int, cmd_func> _cmd_map;
};

#endif /* !ASIOTCPCLI_HPP_ */
