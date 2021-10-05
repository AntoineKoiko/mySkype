/*
** EPITECH PROJECT, 2021
** babel
** File description:
** babel
*/

#ifndef BABEL_HPP_
#define BABEL_HPP_

#include <asio.hpp>
#include "BabelServer.hpp"

#define UN __attribute__((unused))
#define READ_SIZE 2048
#define MAGIC_NUMBER 753159

typedef struct data_s {
    int magic;
    int code;
    std::size_t size;
    char data[READ_SIZE];
} data_t;

typedef struct header_s {
    int magic;
    int code;
    std::size_t size;
} header_t;

std::shared_ptr<Babel::BabelServer> get_server(bool = false, std::shared_ptr<Babel::BabelServer> = nullptr);

#endif /* !BABEL_HPP_ */
