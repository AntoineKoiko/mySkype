/*
** EPITECH PROJECT, 2021
** babel
** File description:
** call
*/

#ifndef CALL_HPP_
#define CALL_HPP_

#include "Database/User.hpp"
#include <vector>

struct Call {
    Call() {
    }
    int id;
    std::vector<Babel::Server::Db::User> users;
    std::vector<Babel::Server::Db::User> users_requested;
};

#endif /* !CALL_HPP_ */
