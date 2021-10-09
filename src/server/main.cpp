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

int main(int argc, char* argv[])
{
    int port = 9999;

    if (argc > 1)
        port = std::atoi(argv[1]);
    try {
        auto serv = std::make_shared<Babel::BabelServer>(port);

        get_server(true, serv);
        serv->start();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 84;
    }
    return 0;
}