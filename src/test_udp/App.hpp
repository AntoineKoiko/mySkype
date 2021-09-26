/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** App
*/

#ifndef APP_HPP_
#define APP_HPP_

#include <QObject>
#include <QSocketNotifier>
#include <iostream>
#include "Udp.hpp"

class App : public QObject {

    Q_OBJECT;

    public:
        App(int senderPort, int receiverPort);
        ~App();

        void run();

    signals:
        void quit();

    private:
        int _senderPort;
        int _receiverPort;
        Udp _udp;
        QSocketNotifier *m_notifier;

    private slots:
        void readCommand();
};



#endif /* !APP_HPP_ */
