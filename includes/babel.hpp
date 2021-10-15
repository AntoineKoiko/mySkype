/*
** EPITECH PROJECT, 2021
** babel
** File description:
** babel
*/

#ifndef BABEL_HPP_
#define BABEL_HPP_

#include <asio.hpp>

#define UN [[maybe_unused]]
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

namespace Babel::Res
{
    const int CONNECTION_ACCEPTED = 200;
    const int LOGGED_IN = 201;
    const int ACCEPT_CTC_REQ = 203;
    const int DISMISS_CTC_REQ = 204;
    const int CONTACTS_LIST = 206;
    const int NEW_CONTACT_REQ = 207;
    const int BAD_REQUEST = 400;
    const int ALREADY_LOGGED = 401;
    const int NOT_AUTHORIZED = 403;
    const int COMMAND_NOT_FOUND = 404;
    const int SERVER_ERROR = 500;
    const int CALL_TAKEN = 208;
    const int CALL_ACCEPTED = 209;
    const int JOIN_CALL = 210;
    const int CALL_REQUEST = 211;
}

namespace Babel::Req
{
    const int LOGIN = 000;
    const int ADD_CONTACT = 001;
    const int ACCEPT_CONTACT = 002;
    const int REJECT_CONTACT = 003;
    const int REMOVE_CONTACT = 004;
    const int GET_CONTACT_LIST = 005;
    const int CALL_SOMEONE = 100;
    const int ACCEPT_CALL = 101;
    const int REJECT_CALL = 102;
    const int HANG_UP = 103;
}

#endif /* !BABEL_HPP_ */
