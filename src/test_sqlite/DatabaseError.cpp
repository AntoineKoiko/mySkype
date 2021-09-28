/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Database Error
*/

#include "DatabaseError.hpp"

DatabaseError::DatabaseError(const std::string message)
{
    _message = message;
}

const char *DatabaseError::what() const noexcept
{
    return _message.c_str();
}