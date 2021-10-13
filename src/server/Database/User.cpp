/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** User
*/

#include "User.hpp"

using namespace Babel::Server::Db;

User::User() : _name(""), _exists(false), _isConnected(false)
{
}

User::~User() {}

bool User::operator==(const User &rhs) const
{
    return _name == rhs._name;
}