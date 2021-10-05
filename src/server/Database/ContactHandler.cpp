/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Contact Handler
*/

#include "../../../includes/server/Database/ContactHandler.hpp"

using namespace Babel;

ContactHandler::ContactHandler(DatabaseManager &dbManager) : _dbManager(dbManager)
{
    std::vector<std::pair<const std::string, const std::string>> contactDescription =
    {{"pseudo", "text"}, {"owner", "text"}};
    std::vector<std::pair<const std::string, const std::string>> contactRequestDescription =
    {{"pseudo", "text"}, {"owner", "text"}};

    if (!(_dbManager.checkIfTableExist(CONTACT_TABLE_NAME))) {
        _dbManager.createTable(CONTACT_TABLE_NAME, CONTACT_PRIMARY_KEY_NAME, contactDescription);
    }
    if (!(_dbManager.checkIfTableExist(CONTACT_REQUEST_TABLE_NAME))) {
        _dbManager.createTable(CONTACT_REQUEST_TABLE_NAME, CONTACT_PRIMARY_KEY_NAME, contactRequestDescription);
    }
}

ContactHandler::~ContactHandler() {}

void ContactHandler::addContact(const std::string &owner, const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> contactRequestSearched
    = {{"owner", "text", owner}, {"pseudo", "text", name}};
    std::vector<std::tuple<const std::string, const std::string>> newContact
    = {{"int", std::to_string(_dbManager.getNextFreePrimaryKey(CONTACT_TABLE_NAME, CONTACT_PRIMARY_KEY_NAME))},
    {"text", name}, {"text", owner}};

    _dbManager.addEntry(CONTACT_TABLE_NAME, newContact);
}

void ContactHandler::removeContact(const std::string &owner, const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> contactSearched
    = {{"owner", "text", owner}, {"pseudo", "text", name}};

    _dbManager.deleteEntry(CONTACT_TABLE_NAME, contactSearched);
}

std::vector<Contact> ContactHandler::getListOfContact(const std::string &owner) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> contactSearched
    = {{"owner", "text", owner}};
    std::vector<std::vector<std::string>> contactTable =
    _dbManager.getEntry(CONTACT_TABLE_NAME, contactSearched);
    std::vector<Contact> listOfContact = {};
    Contact contact;

    for (auto &entry : contactTable) {
        contact._name = entry[1];
        contact._owner = entry[2];
        listOfContact.push_back(contact);
    }
    return listOfContact;
}

void ContactHandler::addContactRequest(const std::string &owner, const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> contactRequestSearched
    = {{"owner", "text", owner}, {"pseudo", "text", name}};
    
    if (_dbManager.getEntry(CONTACT_REQUEST_TABLE_NAME, contactRequestSearched).size() != 0)
        return;

    std::vector<std::tuple<const std::string, const std::string>> newContactRequest
    = {{"int", std::to_string(_dbManager.getNextFreePrimaryKey(CONTACT_REQUEST_TABLE_NAME, CONTACT_PRIMARY_KEY_NAME))},
    {"text", name}, {"text", owner}};

    _dbManager.addEntry(CONTACT_REQUEST_TABLE_NAME, newContactRequest);
}

void ContactHandler::acceptContactRequest(const std::string &owner, const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> contactRequestSearched
    = {{"owner", "text", owner}, {"pseudo", "text", name}};
    std::vector<std::vector<std::string>> contactRequest = _dbManager.getEntry(CONTACT_REQUEST_TABLE_NAME, contactRequestSearched);

    if (contactRequest.size() == 0)
        return;

    std::vector<std::tuple<const std::string, const std::string>> newContact
    = {{"int", std::to_string(_dbManager.getNextFreePrimaryKey(CONTACT_TABLE_NAME, CONTACT_PRIMARY_KEY_NAME))},
    {"text", name}, {"text", owner}};

    _dbManager.addEntry(CONTACT_TABLE_NAME, newContact);
    _dbManager.deleteEntry(CONTACT_REQUEST_TABLE_NAME, contactRequestSearched);
}

void ContactHandler::dismissContactRequest(const std::string &owner, const std::string &name) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> contactRequestSearched
    = {{"owner", "text", owner}, {"pseudo", "text", name}};

    _dbManager.deleteEntry(CONTACT_REQUEST_TABLE_NAME, contactRequestSearched);
}

std::vector<Contact> ContactHandler::getListOfContactRequest(const std::string &owner) const
{
    std::vector<std::tuple<const std::string, const std::string, const std::string>> contactRequestSearched
    = {{"owner", "text", owner}};
    std::vector<std::vector<std::string>> contactRequestTable =
    _dbManager.getEntry(CONTACT_REQUEST_TABLE_NAME, contactRequestSearched);
    std::vector<Contact> listOfContactRequest = {};
    Contact contactRequest;

    for (auto &entry : contactRequestTable) {
        contactRequest._name = entry[1];
        contactRequest._owner = entry[2];
        listOfContactRequest.push_back(contactRequest);
    }
    return listOfContactRequest;
}