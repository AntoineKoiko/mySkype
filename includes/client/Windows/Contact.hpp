/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Contact
*/

#ifndef CONTACT_HPP_
#define CONTACT_HPP_

#include <string>

class Contact
{
public:
    Contact(const std::string &username);
    ~Contact();

    std::string get_username() const noexcept;

private:
    std::string _username;
};

#endif /* !CONTACT_HPP_ */
