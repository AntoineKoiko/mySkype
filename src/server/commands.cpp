/*
** EPITECH PROJECT, 2021
** babel
** File description:
** commands
*/

#include "AsioTCPCli.hpp"
#include "UserHandler.hpp"
#include "ContactHandler.hpp"
#include "utils.hpp"

using namespace Babel::Server;

static int sendAllRequests(const std::string &owner, Db::ContactHandler &handler, Network::AsioTCPCli &client)
{
    auto contacts = handler.getListOfContactRequest(owner);

    for (auto it = contacts.cbegin(); it != contacts.cend(); ++it) {
        client.write(Babel::Res::NEW_CONTACT_REQ, it->_owner.c_str());
        std::cout << it->_owner << " request to " << it->_name << " has been send" << std::endl;
    }
    return 0;
}

int Network::AsioTCPCli::login(const std::string &username)
{
    std::cout << "Client : " << this->getIpString() << " trying to log in as " << username << std::endl;
    auto serv = get_server();
    auto userHandler = serv->getUserHandler();
    auto contactHandler = serv->getContactHandler();
    Db::User user = userHandler.getUser(username);

    if (user._exists) {
        if (serv->getServer().isUserLogged(username)) {
            write(Babel::Res::ALREADY_LOGGED, username.c_str());
            return 1;
        }
        this->_connectedUser = std::make_shared<Db::User>(user);
        write(Babel::Res::LOGGED_IN, username.c_str());
        std::cout << this->_connectedUser->_name << " has logged in" << std::endl;
        sendAllRequests(this->_connectedUser->_name, contactHandler, *this);
    } else {
        serv->getUserHandler().addUser(username);
        user = userHandler.getUser(username);
        this->_connectedUser = std::make_shared<Db::User>(user);
        write(Babel::Res::LOGGED_IN, username.c_str());
        std::cout << this->_connectedUser << " has been created and logged in" << std::endl;
        sendAllRequests(this->_connectedUser->_name, contactHandler, *this);
    }
    return 0;
}

int Network::AsioTCPCli::addContactRequest(const std::string &username)
{
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    const std::string owner = this->getConnectedUser()->_name;
    const Db::User user = userHandler.getUser(username);
    Network::AsioTCPCli *user_client = serv->getServer().isUserLogged(user._name);

    if (!this->_connectedUser) {
        write(Babel::Res::NOT_AUTHORIZED, "Not Connected"); // TODO: change for real code
        return 1;
    }
    if (!user._exists) {
        write(Babel::Res::BAD_REQUEST, "Doesn't exists"); // TODO: change for real code
        return 1;
    }
    if (owner == username) {
        write(Babel::Res::BAD_REQUEST, "Impossible to add yourself as contact");
        return 1;
    }
    if (contactHandler.addContactRequest(owner, username) == 1) {
        write(Babel::Res::BAD_REQUEST, "Request or Contact already exist");
        return 1;
    }
    if (user_client)
        user_client->write(Babel::Res::NEW_CONTACT_REQ, owner.c_str());
    this->write(205, username.c_str());
    return 0;
}

static bool checkContactRequest(const Db::ContactHandler &handler, const std::string &username, const std::string &owner)
{
    auto ownerRequests = handler.getListOfContactRequest(username);

    for (auto it = ownerRequests.cbegin(); it != ownerRequests.cend(); ++it) {
        if (it->_owner == owner) {
            return true;
        }
    }
    return false;
}

static bool checkContact(const Db::ContactHandler &handler, const std::string &username, const std::string &owner)
{
    auto contacts = handler.getListOfContact(owner);

    for (auto it = contacts.cbegin(); it != contacts.cend(); ++it) {
        if (it->_name == username) {
            return true;
        }
    }
    return false;
}

int Network::AsioTCPCli::acceptContact(const std::string &username)
{
    Network::AsioTCPCli *requestOwner;

    if (!this->_connectedUser) {
        write(Babel::Res::NOT_AUTHORIZED, "You must be logged in");
        return 1;
    }
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    Db::User user = userHandler.getUser(username);

    if (user._exists) {
        if (!checkContactRequest(contactHandler, this->_connectedUser->_name, username)) {
            write(Babel::Res::BAD_REQUEST, "Contact request not found");
            return 1;
        }
        contactHandler.acceptContactRequest(username, this->_connectedUser->_name);
        requestOwner = serv->getServer().isUserLogged(username);
        requestOwner->write(Babel::Res::ACCEPT_CTC_REQ, this->_connectedUser->_name.c_str());
    }
    return 0;
}

int Network::AsioTCPCli::denyContact(const std::string &username)
{
    if (!this->_connectedUser) {
        write(Babel::Res::NOT_AUTHORIZED, "You must be logged in");
        return 1;
    }
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    Db::User user = userHandler.getUser(username);

    if (user._exists) {
        if (!checkContactRequest(contactHandler, this->_connectedUser->_name, username)) {
            write(Babel::Res::BAD_REQUEST, "Request not found");
            return 1;
        }
        contactHandler.dismissContactRequest(username, this->_connectedUser->_name);
    }
    return 0;
}

int Network::AsioTCPCli::delContact(const std::string &username)
{
    if (!this->_connectedUser) {
        write(Babel::Res::NOT_AUTHORIZED, "You must be logged in");
        return 1;
    }
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    Db::User user = userHandler.getUser(username);

    if (user._exists) {
        if (!checkContact(contactHandler, username, this->_connectedUser->_name)) {
            write(Babel::Res::BAD_REQUEST, "Contact not found");
            return 1;
        }
        contactHandler.removeContact(this->_connectedUser->_name, username);
    }
    return 0;
}

int Network::AsioTCPCli::getContacts(const std::string &username)
{
    if (!this->_connectedUser) {
        write(Babel::Res::NOT_AUTHORIZED, "You must be looged in");
        return 1;
    }
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    Db::User user = userHandler.getUser(username);
    std::vector<Db::Contact> contactsList;
    std::string data;

    if (user._exists) {
        contactsList = contactHandler.getListOfContact(user._name);
        for (auto &contact : contactsList) {
            data.append(contact._name);
            data.append(";");
        }
        write(Babel::Res::CONTACTS_LIST, data.c_str());
    }
    return 0;
}