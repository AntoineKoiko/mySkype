/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** User
*/

#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include <tuple>

#include <stdio.h>

namespace Babel::Server {
    class User
    {
        public :
            User();
            ~User();

            std::string _name;
            bool _exists;
            bool _isConnected;

        protected :

        private :

    };
}

#endif /* !USER_HPP */
