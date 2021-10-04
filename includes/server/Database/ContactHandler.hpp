/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Contact Handler
*/

#ifndef CONTACT_HANDLER_HPP
#define CONTACT_HANDLER_HPP

#include <string>

#include "DatabaseManager.hpp"
#include "Contact.hpp"

#define CONTACT_TABLE_NAME "contact"
#define CONTACT_REQUEST_TABLE_NAME "contactRequest"

#define CONTACT_PRIMARY_KEY_NAME "id"

namespace Babel {
    class ContactHandler
    {
        public :
            ContactHandler(DatabaseManager &dbManager);
            ~ContactHandler();

            void addContact(const std::string &owner, const std::string &name) const;
            void removeContact(const std::string &owner, const std::string &name) const;

            std::vector<Contact> getListOfContact(const std::string &owner) const;

            void addContactRequest(const std::string &owner, const std::string &name) const;

            void acceptContactRequest(const std::string &owner, const std::string &name) const;
            void dismissContactRequest(const std::string &owner, const std::string &name) const;

            std::vector<Contact> getListOfContactRequest(const std::string &owner) const;

        protected :

        private :
            DatabaseManager _dbManager;
    };
}

#endif /* !CONTACT_HANDLER_HPP */
