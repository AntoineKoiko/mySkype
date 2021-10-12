/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** InputChecker
*/

#ifndef INPUTCHECKER_HPP_
#define INPUTCHECKER_HPP_

#include <string>
#include <algorithm>

class InputChecker
{
public:
    /*
    //return:
    //1 -> invalid char
    //2 -> missing letter
    //0 -> all ok
    */
    static int checkLoginInput(const std::string &str) noexcept;
};

#endif /* !INPUTCHECKER_HPP_ */
