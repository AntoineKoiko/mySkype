/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Udp
*/

#include "Udp.hpp"

Udp::Udp(const int port, QObject *parent) : QObject(parent)
{
    _socket = std::make_unique<QUdpSocket>(this);
    _socket->bind(QHostAddress(QString("127.0.0.1")), port);
    connect(_socket.get(), &QUdpSocket::readyRead, this, &Udp::ReceiveDatagrams);

    std::cout << QHostAddress::AnyIPv4 << std::endl;
}

Udp::~Udp()
{
    if (_socket->isOpen()) {
        _socket->close();
    }
}

QByteArray Udp::serialize(const packet_t &packet)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_4_5);

    try {
        stream  << packet.timestamp
            << packet.msg.c_str();
    } catch (...) {
        std::cout << "Error" << std::endl;
    }

    return byteArray;
}

packet_t Udp::deserialize(const QByteArray& byteArray)
{
    packet_t myPacket;
    QDataStream stream(byteArray);
    stream.setVersion(QDataStream::Qt_4_5);
    char *str;

    stream >> myPacket.timestamp
           >> str;
    myPacket.msg = std::string(str);
    return myPacket;
}

void Udp::ReceiveDatagrams()
{
    packet_t receivedPacket;
    QByteArray Buffer;
    Buffer.resize(_socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    _socket->readDatagram(Buffer.data(),Buffer.size(),&sender,&senderPort);
    receivedPacket = deserialize(Buffer);

    std::cout << "Addr: " << sender.toString().toStdString() << " Port: "<< senderPort << std::endl;
    std::cout << receivedPacket.timestamp << " ," << receivedPacket.msg << std::endl;
    //send(sender.toString().toStdString(), senderPort, std::string("Hello I'm the server\n"));
}

void Udp::send(const std::string &sender, int port, std::string msg)
{
    packet_t packet;
    packet.msg = std::string(msg);
    packet.timestamp = static_cast<qint64>(std::time(0));

    QHostAddress senderAddr(QString(sender.c_str()));
    QByteArray Data = serialize(packet);

    _socket->writeDatagram(Data, senderAddr, port);
}

#include "moc_Udp.cpp"