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
    return _pendingContact;
}

void ContactHandler::acceptContactRequest(const std::string &username)
{
    std::vector<QString> selected = _pendingContacList->getSelectdQStrItems();

    for (const auto lt : selected)
    {
        _contacList->addItem(lt);
    }
    _pendingContacList->deleteSelectedRow();

    // int idx = -1;

    // for (std::size_t i = 0; i < _pendingContact.size(); i++)
    // {
    //     if (_pendingContact.at(i).get_username() == username)
    //     {
    //         idx = i;
    //         break;
    //     }
    // }
    // if (idx != -1)
    // {
    //     Contact buf{_pendingContact[idx].get_username()};
    //     _pendingContact.erase(_pendingContact.begin() + idx);
    //     _contacts.push_back(username);
    // }
}

void ContactHandler::dismissContactRequest(const std::string &username)
{
    _pendingContacList->deleteSelectedRow();
    // int idx = -1;

    // for (std::size_t i = 0; i < _pendingContact.size(); i++)
    // {
    //     if (_pendingContact.at(i).get_username() == username)
    //     {
    //         idx = i;
    //         break;
    //     }
    // }

    // if (idx != -1)
    //     _pendingContact.erase(_pendingContact.begin() + idx);
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
    this->_pendingContact.push_back(Contact{username});
    _pendingContacList->addItem(QString::fromStdString(username));
    return true;
}

bool ContactHandler::makeContactRequest(const std::string &username)
{
    //need to have NetworkAPI
    // if we decide to send packet from here
}
