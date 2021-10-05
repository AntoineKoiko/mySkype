/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Contact
*/

#include "Contact.hpp"

Contact::Contact(const std::string &username)
{
    _username = username;
}

Contact::~Contact()
{
}

std::string Contact::get_username() const noexcept
{
    return _username;
}
