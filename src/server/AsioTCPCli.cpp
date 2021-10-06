/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPCli
*/

#include "babel.hpp"
#include "AsioTCPCli.hpp"
#include <iostream>

AsioTCPCli::AsioTCPCli(asio::io_context &context)
: _socket(context), _connected_user(nullptr)
{
    _cmd_map[000] = &AsioTCPCli::login;
    _cmd_map[001] = &AsioTCPCli::addContactRequest;
    _cmd_map[002] = &AsioTCPCli::addContact;
    // _cmd_map[003] = &AsioTCPCli::delContact;
}

AsioTCPCli::~AsioTCPCli()
{
}

asio::ip::tcp::socket &AsioTCPCli::getSocket()
{
    return _socket;
}

const std::string AsioTCPCli::get_ip_string() const
{
    try {
        return _socket.remote_endpoint().address().to_string();
    } catch (const std::exception &err) {
        std::cerr << "Error : " << err.what() << std::endl;
        return "error";
    }
}

void AsioTCPCli::handle_read(const asio::error_code &err, const std::size_t bytes)
{
    if (err) {
        std::cerr << "Error : " << err.message() << std::endl;
        return;
    }
    if (bytes <= 0)
        return;
    DataPacket *data = (DataPacket *)&_buffer[0];
    if (data->magic != MAGIC_NUMBER) {
        std::cerr << "Error : wrong magic number" << std::endl;
        return;
    }
    if (bytes > 0 && data->size > 0) {
        auto it = _cmd_map.find(data->code);

        if (it != _cmd_map.end())
            (this->*(it->second))(data->data);
        else
            write(500, "Error");
    }
}

void AsioTCPCli::read()
{
    auto handler = std::bind(&AsioTCPCli::handle_read, this, std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(_buffer, sizeof(DataPacket)), handler);
}

void AsioTCPCli::handle_write(const asio::error_code &error, UN const std::size_t bytes)
{
    if (error) {
        std::cerr << "Error: " << error.message() << std::endl;
    }
}

void AsioTCPCli::write(int code, const char data[])
{
    DataPacket data_struct;

    data_struct.code = code;
    data_struct.size = strlen(data);
    DataPacket *data_struct_ptr = &data_struct;
    auto handler = std::bind(&AsioTCPCli::handle_write, this, std::placeholders::_1, std::placeholders::_2);

    std::memcpy(data_struct.data, data, data_struct.size);
    _socket.async_write_some(asio::buffer(data_struct_ptr, sizeof(DataPacket)), handler);
}

const std::shared_ptr<Babel::User> AsioTCPCli::getConnectedUser() const
{
    return _connected_user;
}