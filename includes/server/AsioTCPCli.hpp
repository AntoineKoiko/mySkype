/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPCli
*/

#ifndef ASIOTCPCLI_HPP_
#define ASIOTCPCLI_HPP_

#include <asio.hpp>

class AsioTCPCli {
    public:
        AsioTCPCli(asio::io_context &);
        ~AsioTCPCli();

        asio::ip::tcp::socket &getSocket();
        std::string get_ip_string() const;

    protected:
    private:
        asio::ip::tcp::socket _socket;
};

#endif /* !ASIOTCPCLI_HPP_ */
