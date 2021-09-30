/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Udp
*/

#ifndef UDP_HPP_
#define UDP_HPP_

#include <memory>
#include <queue>
#include <QUdpSocket>

namespace Babel::Client::Network
{
    class Udp : public QObject {
        Q_OBJECT

        public:
            explicit Udp(const int port, const std::string &hostAddr, QObject *parent = nullptr);
            ~Udp();

            void send(const std::string &sender, int port, const std::vector<char> &packet) const;

        private:
            std::unique_ptr<QUdpSocket> _socket;

        signals:

        public slots:
            void receiveDatagrams() const;
    };
}

#endif /* !UDP_HPP_ */