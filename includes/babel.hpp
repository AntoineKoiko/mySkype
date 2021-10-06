/*
** EPITECH PROJECT, 2021
** babel
** File description:
** babel
*/

#ifndef BABEL_HPP_
#define BABEL_HPP_

#include <asio.hpp>

#define UN __attribute__((unused))
#define READ_SIZE 2048
#define MAGIC_NUMBER 753159

struct DataPacket {
    DataPacket() {
        this->magic = MAGIC_NUMBER;
        this->code = 0;
        this->size = 0;
        std::memset(this->data, 0, READ_SIZE * sizeof(char));
    }
    int magic;
    int code;
    std::size_t size;
    char data[READ_SIZE];
};

#endif /* !BABEL_HPP_ */
