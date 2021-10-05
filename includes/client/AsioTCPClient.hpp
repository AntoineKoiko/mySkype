/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPClient
*/

#ifndef ASIOTCPCLIENT_HPP_
#define ASIOTCPCLIENT_HPP_

#include "asio.hpp"
#include "babel.hpp"

class AsioTCPClient : public std::enable_shared_from_this<AsioTCPClient> {
    public:
        AsioTCPClient();
        AsioTCPClient(const std::string &, const int &);
        ~AsioTCPClient();

        void read();
        void run();
        void write(int code, char data[2048]);
        void handle_read(const asio::error_code &, const std::size_t);
        void handle_write(const asio::error_code &, const std::size_t);

    protected:
    private:
        asio::io_context _context;
        asio::ip::tcp::socket _socket;
        unsigned char _buffer[2048];
};

#endif /* !ASIOTCPCLIENT_HPP_ */
