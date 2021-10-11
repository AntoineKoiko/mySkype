/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** InputChecker
*/

#include "InputChecker.hpp"

int InputChecker::checkLoginInput(const std::string &str) noexcept
{
    for (const char &c : str)
    {
        if (!isalnum(c) && c != '-' && c != '_')
            return 1;
    }
    if (std::any_of(std::begin(str), std::end(str), ::isalpha))
        return 0;
    return 2;
}
