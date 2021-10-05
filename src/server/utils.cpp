/*
** EPITECH PROJECT, 2021
** babel
** File description:
** utils
*/

#include "BabelServer.hpp"
#include <memory>

std::shared_ptr<Babel::BabelServer> get_server(bool set = false, std::shared_ptr<Babel::BabelServer> serv_ptr = nullptr)
{
    static std::shared_ptr<Babel::BabelServer> serv = nullptr;

    if (set)
        serv = serv_ptr;
    return serv;
}