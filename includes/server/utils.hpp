/*
** EPITECH PROJECT, 2021
** babel
** File description:
** utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "BabelServer.hpp"

std::shared_ptr<Babel::Server::BabelServer> get_server(bool = false, std::shared_ptr<Babel::Server::BabelServer> = nullptr);

#endif /* !UTILS_HPP_ */
