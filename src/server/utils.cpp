/*
** EPITECH PROJECT, 2021
** babel
** File description:
** utils
*/

#include "BabelServer.hpp"
#include <memory>

using namespace Babel::Server;

std::shared_ptr<BabelServer> get_server(bool set = false, std::shared_ptr<BabelServer> serv_ptr = nullptr)
{
    static std::shared_ptr<BabelServer> serv = nullptr;

    if (set)
        serv = serv_ptr;
    return serv;
}