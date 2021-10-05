/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPClient
*/

#include "AsioTCPClient.hpp"

AsioTCPClient::AsioTCPClient() : _context(), _socket(_context)
{
    _socket.connect(
        asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"),
        9999
    ));
}

AsioTCPClient::AsioTCPClient(const std::string &ip, const int &port)
: _context(), _socket(_context)
{
    _socket.connect(
        asio::ip::tcp::endpoint(asio::ip::address::from_string(ip),
        port
    ));
}

AsioTCPClient::~AsioTCPClient()
{
}

static void handle_data_read(const data_t &data, UN const asio::error_code err, UN const std::size_t bytes)
{
    std::cout << "received: " << data.data << std::endl;
    // TODO: make the command handler
}

void AsioTCPClient::handle_read(UN const asio::error_code &err, const std::size_t bytes)
{
    if (bytes <= 0)
        return;

    data_t *data = (data_t *)&_buffer[0];
    if (data->magic != MAGIC_NUMBER) {
        std::cerr << "GET OUT OF HERE YOU DEMON" << std::endl;
        return;
    }
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "buffer : " << _buffer << std::endl << std::endl;
    std::cout << "buffer info :" << std::endl
    << "code : " << data->code << " size : " << data->size << std::endl;
    /*
    if (data.size > 0) {
        std::cout << "triggered2" << std::endl;
        auto handler = std::bind(&handle_data_read, data, std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(data.data, data.size), handler);
    } */
}

void AsioTCPClient::read()
{
    auto handler = std::bind(&AsioTCPClient::handle_read, this, std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(_buffer, sizeof(data_t)), handler);
}

void AsioTCPClient::handle_write(UN const asio::error_code &err, UN const std::size_t bytes)
{
}

void AsioTCPClient::write(int code, char data[2048])
{
}

void AsioTCPClient::run()
{
    _context.run();
}