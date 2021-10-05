/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Udp
*/

#include "Udp.hpp"

using namespace Babel::Client::Network;

Udp::Udp(Babel::Client::Audio::ICallHandler *callHandler, QObject *parent) : _socket(nullptr), _callHandler(callHandler), QObject(parent)
{
}

Udp::~Udp()
{
    if (_socket != nullptr && _socket->isOpen()) {
        _socket->close();
    }
}

void Udp::connect(const int port, const std::string &hostAddr)
{
    _socket = std::make_unique<QUdpSocket>(this);
    _socket->bind(QHostAddress(QString(hostAddr.c_str())), port);
    QObject::connect(_socket.get(), &QUdpSocket::readyRead, this, &Udp::receiveDatagrams);
}

void Udp::receiveDatagrams() const
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;

    buffer.resize(_socket->pendingDatagramSize());
    _socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    std::vector<char> bufferToCompress(buffer.begin(), buffer.end());
    _callHandler->dataPacketAvailable(bufferToCompress);
    (void)buffer;
    (void)sender;
    (void)senderPort;
}

void Udp::send(const std::string &sender, int port, const std::vector<char> &packet) const
{
    QHostAddress senderAddr(QString(sender.c_str()));
    QByteArray data(packet.data(), packet.size());

    _socket->writeDatagram(data, senderAddr, port);
}

#include "moc_Udp.cpp"