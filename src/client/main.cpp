/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** main
*/

#include <QApplication>
#include "MyWindow.hpp"
#include "TcpClient.hpp"
#include "UserHandler.hpp"
#include <memory>

using namespace Babel::Client;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto client = std::make_shared<Network::TcpClient>();
    auto userHandler = std::make_shared<UserHandler>(client);
    std::unique_ptr<MyWindow> window = nullptr;
    int port = 0;

    if (argc != 3) {
        std::cerr << "Invalid argument number: ./babel_client host port" << std::endl;
        return 84;
    }
    port = std::atoi(argv[2]);
    if (port == 0) {
        return 84;
    }
    try {
        window = std::make_unique<MyWindow>(userHandler, client);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    client->connect(argv[1], port);
    window->show();
    return app.exec();
}