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
//    _toRead = 0;
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

std::vector<char> TcpClient::getData()
{
    std::vector<char> data;

    data.resize(0);
    while (_dataPacket.empty()) {
        std::cout << "C'EST VIIIIIIIIIDE PUTAING" << std::endl;
    }
    if (_dataPacket.empty()) {
        std::cout << "Aucun packet en attente !" << std::endl;
        return data;
    }
    data = this->_dataPacket.front();
    this->_dataPacket.pop();
    return data;
}

void TcpClient::socketReadyRead()
{
    std::vector<char> container;
    container.resize(sizeof(DataPacket));
//    qint64 nbBytesRead = 0;
//    qint64 readState = 0;
    //std::cout << "Read size : " << sizeof(DataPacket) << std::endl;

    //while (nbBytesRead != sizeof(DataPacket)) {
//        std::cout << "\nbytesread in read: " << sizeof(DataPacket) + _toRead << std::endl << std::endl;
//    nbBytesRead = this->_socket->read(container.data(), sizeof(DataPacket) + _toRead);
//    std::cout << "\nbytesread: " << nbBytesRead << std::endl << std::endl;
//    for (size_t i = 0; i < container.size(); i++) {
//        container[i] = container[i + _toRead];
//    }
//    container.resize(sizeof(DataPacket));
//    _toRead = sizeof(DataPacket) + _toRead - nbBytesRead;
//        std::cout << "readState: " << readState << std::endl;
//        if (readState == -1) {
//            std::cout << "readState -1" << std::endl; 
            //break;
//        }
//        nbBytesRead += readState;
//        std::cout << "nbBytesRead: " << nbBytesRead << std::endl;
//        readState = this->_socket->read(container.data()+nbBytesRead, sizeof(DataPacket) - nbBytesRead);
//        std::cout << "readState: " << readState << std::endl;
    //}

    //std::cout << "On recoit un packet de taille : " << this->_socket->read(container.data(), sizeof(DataPacket)) << std::endl;
    this->_socket->read(container.data(), sizeof(DataPacket));
    _dataPacket.push(container);
    emit this->newPacketReceive();
    // std::cout << dataPacket.code << std::endl;
    // std::cout << dataPacket.magic << std::endl;
    // std::cout << dataPacket.size << std::endl;
    // std::cout << dataPacket.data << std::endl;
}

void TcpClient::socketError(int err)
{
    std::cout << "Socket err" << std::endl;
}

#include "moc_TcpClient.cpp"