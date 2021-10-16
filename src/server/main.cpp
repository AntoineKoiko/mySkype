/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** main
*/

#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <asio.hpp>
#include <cstdlib>
#include "BabelServer.hpp"

using namespace Babel::Server;

int main(int argc, char* argv[])
{
    int port = Babel::Server::defaultPort;

    if (argc > 1)
        port = std::atoi(argv[1]);
    try {
        auto serv = std::make_shared<BabelServer>(port);

        get_server(true, serv);
        serv->start();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return Babel::Server::errorCode;
    }
    return Babel::Server::successCode;
}