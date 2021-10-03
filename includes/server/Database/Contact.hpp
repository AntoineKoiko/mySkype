/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Contact
*/

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <vector>
#include <tuple>

#include <stdio.h>

namespace Babel {
    class Contact
    {
        public :
            Contact();
            ~Contact();

            std::string _name;
            std::string _adress;
            std::string _owner;

        protected :

        private :

    };
}

/*
ADD CONTACT
REMOVE CONTACT
GET LIST OF CONTACT
GET LIST OF CONTACT REQUEST
ACCEPT CONTACT REQUEST
REFUSE CONTACT REQUEST
*/

#endif /* !CONTACT_HPP */
