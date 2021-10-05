/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** User Handler
*/

#ifndef USER_HANDLER_HPP
#define USER_HANDLER_HPP

#include <string>

#include "DatabaseManager.hpp"
#include "User.hpp"

#define USER_TABLE_NAME "contact"

#define USER_PRIMARY_KEY_NAME "id"

namespace Babel {
    class UserHandler
    {
        public :
            UserHandler(DatabaseManager &dbManager);
            ~UserHandler();

            void addUser(const std::string &name) const;
            void removeUser(const std::string &name) const;

            std::vector<User> getListOfUser(const std::string &name) const;

        protected :

        private :
            DatabaseManager _dbManager;
    };
}

#endif /* !USER_HANDLER_HPP */
