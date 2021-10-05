// Server-side Synchronous Chatting Application
// using C++ asio

#include "babel.hpp"
#include <iostream>
#include <algorithm>
#include <asio.hpp>

int main(UN int argc, UN char* argv[])
{
    try {
        babel::BabelServer serv;

        serv.start();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}