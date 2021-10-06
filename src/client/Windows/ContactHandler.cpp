/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** ContactHandler
*/

#include "ContactHandler.hpp"

ContactHandler::ContactHandler(ListStrWidget *contact, ListStrWidget *pendingContact)
{
    _contactList = contact;
    _pendingContactList = pendingContact;
    _pendingContactList->addItem("test");
    _pendingContactList->addItem("test1");
    _pendingContactList->addItem("test2");
    this->updateData();
}

ContactHandler::~ContactHandler()
{
}

/////////////////

std::vector<Contact> ContactHandler::getContacts() const noexcept
{
    return _contacts;
}

std::vector<Contact> ContactHandler::getContactRequests() const noexcept
{
    return _pendingContacts;
}

void ContactHandler::acceptContactRequest()
{
    std::vector<std::string> selected = _pendingContactList->getSelectdStrItems();

    for (const std::string lt : selected)
    {
        _contactList->addItem(QString::fromStdString(lt));
    }
    _pendingContactList->deleteSelectedRow();
    this->updateData();
}

void ContactHandler::dismissContactRequest()
{
    _pendingContactList->deleteSelectedRow();
    this->updateData();
}

//add directcly contact after request was accepted from the other guy

bool ContactHandler::addContact(const std::string &username)
{
    this->_contacts.push_back(Contact{username});
    _contactList->addItem(QString::fromStdString(username));
    return true;
}

bool ContactHandler::addContactRequest(const std::string &username)
{
    this->_pendingContacts.push_back(Contact{username});
    _pendingContactList->addItem(QString::fromStdString(username));
    return true;
}

#include <iostream>

bool ContactHandler::makeContactRequest(const std::string &username)
{
    std::cout << "Add " << username << "from handler" << std::endl;
    //need to have NetworkAPI
    // if we decide to send packet from here
    return true;
}

void ContactHandler::updateData() noexcept
{
    std::vector<std::string> contactUsername = _contactList->getStrItems();
    std::vector<Contact> contactBuf;
    std::vector<std::string> pendingUsername = _pendingContactList->getStrItems();
    std::vector<Contact> pendingBuf;

    for (const std::string lt : contactUsername)
        contactBuf.push_back(Contact{lt});
    for (const std::string lt : pendingUsername)
        pendingBuf.push_back(Contact{lt});
    _contacts = contactBuf;
    _pendingContacts = pendingBuf;
}
