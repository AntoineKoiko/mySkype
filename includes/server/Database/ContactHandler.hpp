/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Contact Handler
*/

#ifndef CONTACT_HANDLER_HPP
#define CONTACT_HANDLER_HPP

#include <string>
#include <memory>

#include "DatabaseManager.hpp"
#include "Contact.hpp"
#include "babel.hpp"

#define CONTACT_TABLE_NAME "contact"
#define CONTACT_REQUEST_TABLE_NAME "contactRequest"

#define CONTACT_PRIMARY_KEY_NAME "id"

namespace Babel::Server::Db {
    class ContactHandler
    {
        public :
            ContactHandler(const std::shared_ptr<DatabaseManager> dbManager);
            ~ContactHandler();

            void addContact(const std::string &owner, const std::string &name) const;
            void removeContact(const std::string &owner, const std::string &name) const;

            std::vector<Contact> getListOfContact(const std::string &owner) const;

            void addContactRequest(const std::string &owner, const std::string &name) const;

            void acceptContactRequest(const std::string &owner, const std::string &name) const;
            void dismissContactRequest(const std::string &owner, const std::string &name) const;

            std::vector<Contact> getListOfContactRequest(const std::string &pseudo) const;

        protected :

        private :
            std::shared_ptr<DatabaseManager> _dbManager;
    };
}

#endif /* !CONTACT_HANDLER_HPP */
