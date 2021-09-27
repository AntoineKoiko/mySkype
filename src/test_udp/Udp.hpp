/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Udp
*/

#ifndef UDP_HPP_
#define UDP_HPP_

#include <memory>
#include <QUdpSocket>
#include <QDataStream>
#include <iostream>
#include <ctime>

typedef struct {
    std::string msg;
    quint64 timestamp;
} packet_t;

class Udp : public QObject {
    Q_OBJECT

    public:
        explicit Udp(const int port, QObject *parent = nullptr);
        ~Udp();

        void send(const std::string &sender, int port, std::string msg);
        packet_t deserialize(const QByteArray& byteArray);
        QByteArray serialize(const packet_t &packet);

    private:
        std::unique_ptr<QUdpSocket> _socket;

    signals:

    public slots:
        void ReceiveDatagrams();
};

#endif /* !UDP_HPP_ */