/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** App
*/

#include "App.hpp"

App::App(int senderPort, int receiverPort) :
    _senderPort(senderPort), _receiverPort(receiverPort), _udp(senderPort)
{
    m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
}

App::~App()
{
}

void App::run()
{
    std::cout << "> " << std::flush;
    connect(m_notifier, SIGNAL(activated(int)), this, SLOT(readCommand()));
}

void App::readCommand()
{
    std::string line;
    std::getline(std::cin, line);
    if (std::cin.eof() || line == "quit") {
        std::cout << "Good bye!" << std::endl;
        emit quit();
    } else {
        _udp.send(std::string("127.0.0.1"), _receiverPort, line);
    }

}