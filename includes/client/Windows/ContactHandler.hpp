/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** ContactHandler
*/

#ifndef CONTACTHANDLER_HPP_
#define CONTACTHANDLER_HPP_

#include <vector>
#include <string>

#include "Contact.hpp"

class ContactHandler
{
public:
    ContactHandler();
    ~ContactHandler();

    std::vector<Contact> getContacts() const noexcept;
    std::vector<Contact> getContactRequests() const noexcept;

    void acceptContactRequest(const std::string &username);  //bool or exception if not find
    void dismissContactRequest(const std::string &username); //bool or exception if not find
    bool addContact(const std::string &username);            //-> need to have NetworkAPI

private:
    std::vector<Contact> _contacts;
    std::vector<Contact> _pendingContact;

    //NetWorkApi _netAPI;
};

#endif /* !CONTACTHANDLER_HPP_ */
