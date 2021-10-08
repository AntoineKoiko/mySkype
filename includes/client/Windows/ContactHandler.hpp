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
#include <memory>

#include "Contact.hpp"
#include "ListStrWidget.hpp"
#include "TcpClient.hpp"
#include "DataPacketManager.hpp"

class ContactHandler
{
public:
    ContactHandler(ListStrWidget *contact, ListStrWidget *pendingContact, const std::shared_ptr<Babel::Client::Network::TcpClient> network);
    ~ContactHandler();

    std::vector<Contact> getContacts() const noexcept;
    std::vector<Contact> getContactRequests() const noexcept;

    void acceptContactRequest();                          //bool or exception if not find
    void dismissContactRequest();                         //bool or exception if not find
    bool addContact(const std::string &username);         //-> need to have NetworkAPI
    bool addContactRequest(const std::string &username);  //-> need to have NetworkAPI
    bool makeContactRequest(const std::string &username); //-> need to have NetworkAPI

private:
    std::vector<Contact> _contacts;
    std::vector<Contact> _pendingContacts;
    ListStrWidget *_contactList;
    ListStrWidget *_pendingContactList;
    std::shared_ptr<Babel::Client::Network::TcpClient> _network;

    //update std::vector with content of ListStrWidget
    void updateData() noexcept;

    //NetWorkApi _netAPI;
};

#endif /* !CONTACTHANDLER_HPP_ */
