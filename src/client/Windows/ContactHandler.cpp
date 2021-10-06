/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** ContactHandler
*/

#include "ContactHandler.hpp"

ContactHandler::ContactHandler(ListStrWidget *contact, ListStrWidget *pendingContact)
{
    _contacList = contact;
    _pendingContacList = pendingContact;
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

void ContactHandler::acceptContactRequest(const std::string &username)
{
    std::vector<std::string> selected = _pendingContacList->getSelectdStrItems();

    for (const std::string lt : selected)
    {
        _contacList->addItem(QString::fromStdString(lt));
    }
    _pendingContacList->deleteSelectedRow();
    this->updateData();
}

void ContactHandler::dismissContactRequest(const std::string &username)
{
    _pendingContacList->deleteSelectedRow();
    this->updateData();
}

//add directcly contact after request was accepted from the other guy

bool ContactHandler::addContact(const std::string &username)
{
    this->_contacts.push_back(Contact{username});
    _contacList->addItem(QString::fromStdString(username));
    return true;
}

bool ContactHandler::addContactRequest(const std::string &username)
{
    this->_pendingContacts.push_back(Contact{username});
    _pendingContacList->addItem(QString::fromStdString(username));
    return true;
}

#include <iostream>

bool ContactHandler::makeContactRequest(const std::string &username)
{
    std::cout << "Add " << username << "from handler" << std::endl;
    //need to have NetworkAPI
    // if we decide to send packet from here
}

void ContactHandler::updateData() noexcept
{
    std::vector<std::string> contactUsername = _contacList->getStrItems();
    std::vector<Contact> contactBuf;
    std::vector<std::string> pendingUsername = _pendingContacList->getStrItems();
    std::vector<Contact> pendingBuf;

    for (const std::string lt : contactUsername)
        contactBuf.push_back(Contact{lt});
    for (const std::string lt : pendingUsername)
        pendingBuf.push_back(Contact{lt});
    _contacts = contactBuf;
    _pendingContacts = pendingBuf;
}
