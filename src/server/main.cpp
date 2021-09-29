// Server-side Synchronous Chatting Application
// using C++ asio

#include "babel.hpp"
#include <iostream>
#include <algorithm>
#include <asio.hpp>

int main(UN int argc, UN char* argv[])
{
    AsioTCPServer serv;

    serv.run();
}