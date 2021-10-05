// Server-side Synchronous Chatting Application
// using C++ asio

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
    }
}