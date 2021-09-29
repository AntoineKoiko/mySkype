/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPCli
*/

#include "AsioTCPCli.hpp"
#include <iostream>
#include "babel.hpp"

AsioTCPCli::AsioTCPCli(asio::io_context &context)
: _socket(context)
{
}

AsioTCPCli::~AsioTCPCli()
{
}

asio::ip::tcp::socket &AsioTCPCli::getSocket()
{
    return _socket;
}

std::string AsioTCPCli::get_ip_string() const
{
    try {
        return _socket.remote_endpoint().address().to_string();
    } catch (const std::exception &err) {
        std::cerr << "Error : " << err.what() << std::endl;
        return "error";
    }
}

static void handle_data_read(UN const data_t &data, UN const asio::error_code err, UN const std::size_t bytes)
{
    std::cout << data.data << std::endl;
    // TODO: make the command handler
}

void AsioTCPCli::handle_read(UN const asio::error_code &err, UN const std::size_t bytes)
{
    header_t *header = (header_t *)_buffer;
    data_t data = {
        MAGIC_NUMBER,
        header->code,
        header->size,
        ""
    };

    std::cout << "triggered" << std::endl;
    _buffer[0] = '\0';
    if (data.size > 0 && data.size <= READ_SIZE) {
        auto handler = std::bind(&handle_data_read, data, std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(data.data, data.size), handler);
    }
}

void AsioTCPCli::read()
{
    auto handler = std::bind(&AsioTCPCli::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2);

    _socket.async_read_some(asio::buffer(_buffer, sizeof(header_t)), handler);
}

void AsioTCPCli::handle_write(const asio::error_code &error, UN const std::size_t bytes)
{
    if (error) {
        std::cerr << "Error: " << error.message() << std::endl;
    }
}

void AsioTCPCli::write(int code, char data[READ_SIZE])
{
    data_t data_struct = {
        MAGIC_NUMBER,
        code,
        strlen(data),
        {0},
    };
    unsigned char *to_send = nullptr;
    data_t *data_struct_ptr = &data_struct;
    auto handler = std::bind(&AsioTCPCli::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2);

    std::memcpy(data_struct.data, data, READ_SIZE);
    std::cout << "sending data: " << data_struct.data << std::endl;
    to_send = (unsigned char *)data_struct_ptr;
    _socket.async_write_some(asio::buffer(to_send, sizeof(data_t)), handler);
}