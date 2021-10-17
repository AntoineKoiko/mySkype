/*
** EPITECH PROJECT, 2021
** babel
** File description:
** AsioTCPCli
*/

#include "babel.hpp"
#include "AsioTCPCli.hpp"
#include "utils.hpp"
#include <iostream>

using namespace Babel::Server::Network;

AsioTCPCli::AsioTCPCli(asio::io_context &context)
    : _socket(context), _connectedUser(nullptr)
{
    _cmdMap[Babel::Req::LOGIN] = &AsioTCPCli::login;
    _cmdMap[Babel::Req::ADD_CONTACT] = &AsioTCPCli::addContactRequest;
    _cmdMap[Babel::Req::ACCEPT_CONTACT] = &AsioTCPCli::acceptContact;
    _cmdMap[Babel::Req::REJECT_CONTACT] = &AsioTCPCli::denyContact;
    _cmdMap[Babel::Req::REMOVE_CONTACT] = &AsioTCPCli::delContact;
    _cmdMap[Babel::Req::GET_CONTACT_LIST] = &AsioTCPCli::getContacts;
    _cmdMap[Babel::Req::CALL_SOMEONE] = &AsioTCPCli::callInit;
    _cmdMap[Babel::Req::ACCEPT_CALL] = &AsioTCPCli::callAccept;
    _cmdMap[Babel::Req::REJECT_CALL] = &AsioTCPCli::callReject;
    _cmdMap[Babel::Req::HANG_UP] = &AsioTCPCli::callHangup;
}

AsioTCPCli::~AsioTCPCli()
{
}

asio::ip::tcp::socket &AsioTCPCli::getSocket()
{
    return _socket;
}

const std::string AsioTCPCli::getIpString() const
{
    try
    {
        return _socket.remote_endpoint().address().to_string();
    }
    catch (const std::exception &err)
    {
        std::cerr << "Error : " << err.what() << std::endl;
        return "error";
    }
}

static bool removeFromCallByUsername(const std::string &username)
{
    auto serv = get_server();
    auto call = serv->getServer()->getUserCall(username);

    if (call == nullptr) {
        return true;
    }
    for (std::size_t i = 0; i < call->users.size(); i++)
    {
        if (call->users[i]._name == username)
            call->users.erase(call->users.begin() + i);
    }
    for (std::size_t i = 0; i < call->users_requested.size(); i++)
    {
        if (call->users_requested[i]._name == username)
            call->users_requested.erase(call->users_requested.begin() + i);
    }
    return true;
}

void AsioTCPCli::handleRead(const asio::error_code &err, const std::size_t bytes)
{
    auto serv = get_server();

    if (err == asio::error::eof || err == asio::error::connection_reset)
    {
        std::cout << (this->_connectedUser ? this->_connectedUser->_name : "unknow") << " disconnected" << std::endl;
        if (this->_connectedUser && _connectedUser->_exists)
            removeFromCallByUsername(_connectedUser->_name);
        this->_socket.close();
        serv->getServer()->disconnectClient();
        return;
    }
    else if (err)
    {
        std::cerr << "Error : " << err.message() << std::endl;
        return;
    }
    if (bytes <= 0)
        return;
    DataPacket *data = (DataPacket *)&_buffer[0];
    std::cout << "Request code: " << data->code << std::endl;
    if (data->magic != MAGIC_NUMBER)
    {
        std::cerr << "Error : wrong magic number" << std::endl;
        this->read();
        return;
    }
    if ((bytes > 0 && data->size > 0) || data->code == Babel::Req::ACCEPT_CALL || data->code == Babel::Req::HANG_UP)
    {
        auto it = _cmdMap.find(data->code);

        if (it != _cmdMap.end())
            (this->*(it->second))(data->data);
        else
            write(Babel::Res::COMMAND_NOT_FOUND, "Error");
    }
    this->read();
}

void AsioTCPCli::read()
{
    auto handler = std::bind(&AsioTCPCli::handleRead, this, std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(_buffer, sizeof(DataPacket)), handler);
}

void AsioTCPCli::handleWrite(int code, const asio::error_code &error, const std::size_t bytes)
{
    if (error)
    {
        std::cerr << "Error: " << error.message() << std::endl;
    }
    if (bytes) {
        if (_connectedUser) {
            std::cout << "Code : " << code << " user: " << _connectedUser->_name << " bytes: " << bytes << std::endl;
        } else {
            std::cout << "Code : " << code << " bytes: " << bytes << std::endl;
        }
    }
}

void AsioTCPCli::write(int code, const char data[])
{
    DataPacket data_struct;

    data_struct.code = code;
    data_struct.size = strlen(data);
    DataPacket *data_struct_ptr = &data_struct;
    auto handler = std::bind(&AsioTCPCli::handleWrite, this, data_struct.code, std::placeholders::_1, std::placeholders::_2);

    std::memcpy(data_struct.data, data, data_struct.size);
    _socket.async_write_some(asio::buffer(data_struct_ptr, sizeof(DataPacket)), handler);
}

const std::shared_ptr<Babel::Server::Db::User> AsioTCPCli::getConnectedUser() const
{
    return _connectedUser;
}