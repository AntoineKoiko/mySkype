/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** CallHandler
*/

#ifndef CALLHANDLER_HPP_
#define CALLHANDLER_HPP_

#include <string>

class CallHandler
{
public:
    CallHandler();
    ~CallHandler();

    void make_call(const std::string &contact_to_call);

private:
};

#endif /* !CALLHANDLER_HPP_ */
