/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Database Manager Error
*/

#ifndef DATABASE_MANAGER_ERROR_HPP
#define DATABASE_MANAGER_ERROR_HPP

#include <iostream>

class DatabaseManagerError : public std::exception
{
    public:
        DatabaseManagerError(const std::string message);

        const char *what() const noexcept override;

    private:
        std::string _message;
};

#endif /* !DATABASE_MANAGER_ERROR_HPP */
