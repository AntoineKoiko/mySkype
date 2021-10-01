/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Database Manager Error
*/

#include "DatabaseManagerError.hpp"

DatabaseManagerError::DatabaseManagerError(const std::string message)
{
    _message = message;
}

const char *DatabaseManagerError::what() const noexcept
{
    return _message.c_str();
}