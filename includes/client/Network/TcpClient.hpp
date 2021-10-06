/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <memory>
#include <iostream>
#include "babel.hpp"
#include "DataPacketManager.hpp"

namespace Babel::Client::Network
{
    class TcpClient : QObject {
        Q_OBJECT

        public:
            explicit TcpClient(QObject *parent = nullptr);
            ~TcpClient();

            void connect(const std::string &hostAddr, int port);
            void send(const std::vector<char> &packet);

        protected:
        private:
            std::unique_ptr<QTcpSocket> _socket;

        private slots:
            void socketConnected();
            void socketConnectionClosed();
            void socketReadyRead();
            void socketError(int err);
    };
}

#endif /* !TCPCLIENT_HPP_ */
