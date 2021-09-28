/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Database Error
*/

#ifndef DATABASE_ERROR_HPP
#define DATABASE_ERROR_HPP

#include <iostream>

class DatabaseError : public std::exception
{
    public:
        DatabaseError(const std::string message);

        const char *what() const noexcept override;

    private:
        std::string _message;
};

#endif /* !DATABASE_ERROR_HPP */
