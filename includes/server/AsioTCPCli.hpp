/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPCli
*/

#ifndef ASIOTCPCLI_HPP_
#define ASIOTCPCLI_HPP_

#include <asio.hpp>

class AsioTCPCli : public std::enable_shared_from_this<AsioTCPCli> {
    public:
        AsioTCPCli(asio::io_context &);
        ~AsioTCPCli();

        asio::ip::tcp::socket &getSocket();
        const std::string get_ip_string() const;
        void read();
        void write(int code, const char data[2048]);
        void handle_read(const asio::error_code &, const std::size_t);
        void handle_write(const asio::error_code &, const std::size_t);

    protected:
    private:
        asio::ip::tcp::socket _socket;
        unsigned char _buffer[2048];
        std::string _data_buffer;
};

#endif /* !ASIOTCPCLI_HPP_ */
