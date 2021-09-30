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

class Contact
{
public:
    Contact();
    ~Contact();

private:
    std::string _username;
};

Contact::Contact(/* args */)
{
}

Contact::~Contact()
{
}

class ContactHandler
{
public:
    ContactHandler();
    ~ContactHandler();

    // std::vector<Contact> getContactsList() const noexcept;
    // std::vector<Contact> getContactRequests const noexcept:
    // void acceptContactRequest(const std::string &username):
    // void dismissContactRequest(const std::string &username):
    // bool addContact(const std::string &username) const; //-> need to have NetworkAPI

private:
    // std::vector<Contact> _contacts;
    // std::vector<Contact> _pendingContact;

    //NetWorkApi _netAPI;
};

#endif /* !CONTACTHANDLER_HPP_ */
