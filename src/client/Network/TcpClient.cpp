/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** TcpClient
*/

#include "TcpClient.hpp"

using namespace Babel::Client::Network;

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    _socket = std::make_unique<QTcpSocket>();
    QObject::connect(this->_socket.get(), SIGNAL(connected()), this, SLOT(socketConnected()));
    QObject::connect(this->_socket.get(), SIGNAL(disconnected()), this, SLOT(socketConnectionClosed()));
    QObject::connect(this->_socket.get(), SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    QObject::connect(this->_socket.get(), SIGNAL(error(int)), this, SLOT(socketError(int)));
}

TcpClient::~TcpClient()
{
}

void TcpClient::connect(const std::string &serverIp, int port)
{
    QHostAddress serverAdr(QString(serverIp.c_str()));
    _socket->connectToHost(serverAdr, port);
    if (!_socket->waitForConnected(5000)) {
        std::cout << "Failed to connect" << std::endl;
    }
}

void TcpClient::send(const std::vector<char> &packet)
{
    this->_socket->write(packet.data(), packet.size());
}

void TcpClient::socketConnected()
{
    std::cout << "Connected" << std::endl;
}

void TcpClient::socketConnectionClosed()
{
    std::cout << "Connection Closed" << std::endl;
}

void TcpClient::socketReadyRead()
{
    std::vector<char> container;
    container.resize(sizeof(DataPacket));

    this->_socket->read(container.data(), sizeof(DataPacket));
    DataPacket dataPacket = DataPacketManager::deserialize(container);
    std::cout << dataPacket.code << std::endl;
    std::cout << dataPacket.magic << std::endl;
    std::cout << dataPacket.size << std::endl;
    std::cout << dataPacket.data << std::endl;
}

void TcpClient::socketError(int err)
{
    std::cout << "Socket err" << std::endl;
}

#include "moc_TcpClient.cpp"