/*
** EPITECH PROJECT, 2021
** babel
** File description:
** commands
*/

#include "AsioTCPCli.hpp"
#include "Database/UserHandler.hpp"
#include "Database/ContactHandler.hpp"
#include "utils.hpp"

using namespace Babel;

static int sendAllRequests(const std::string &owner, ContactHandler &handler, AsioTCPCli &client)
{
    auto contacts = handler.getListOfContactRequest(owner);

    for (auto it = contacts.cbegin(); it != contacts.cend(); ++it) {
        client.write(207, it->_owner.c_str());
        std::cout << it->_owner << " request to " << it->_name << " has been send" << std::endl;
    }
    return 0;
}

int AsioTCPCli::login(const std::string &username)
{
    std::cout << "Client : " << this->get_ip_string() << " trying to log in as " << username << std::endl;
    auto serv = get_server();
    auto userHandler = serv->getUserHandler();
    auto contactHandler = serv->getContactHandler();
    User user = userHandler.getUser(username);

    if (user._exists) {
        // if (serv->getServer().isUserLogged(username)) {
        //     write(401, username.c_str());
        //     return 1;
        // }
        this->_connected_user = std::make_shared<User>(user);
        write(201, username.c_str());
        std::cout << this->_connected_user->_name << " has logged in" << std::endl;
        sendAllRequests(this->_connected_user->_name, contactHandler, *this);
    } else {
        serv->getUserHandler().addUser(username);
        user = userHandler.getUser(username);
        this->_connected_user = std::make_shared<User>(user);
        write(201, username.c_str());
        std::cout << this->_connected_user << " has been created and logged in" << std::endl;
        sendAllRequests(this->_connected_user->_name, contactHandler, *this);
    }
    return 0;
}

int AsioTCPCli::addContactRequest(const std::string &username)
{
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    const std::string owner = this->getConnectedUser()->_name;
    const User user = userHandler.getUser(username);
    AsioTCPCli *user_client = serv->getServer().isUserLogged(user._name);

    if (!this->_connected_user) {
        write(500, "Not Connected"); // TODO: change for real code
        return 1;
    }
    if (!user._exists) {
        write(500, "Doesn't exists"); // TODO: change for real code
        return 1;
    }
    contactHandler.addContactRequest(owner, username);
    if (user_client)
        user_client->write(207, owner.c_str());
    return 0;
}

static bool checkContactRequest(const ContactHandler &handler, const std::string &username, const std::string &owner)
{
    auto ownerRequests = handler.getListOfContactRequest(username);

    for (auto it = ownerRequests.cbegin(); it != ownerRequests.cend(); ++it) {
        if (it->_owner == owner) {
            return true;
        }
    }
    return false;
}

static bool checkContact(const ContactHandler &handler, const std::string &username, const std::string &owner)
{
    auto contacts = handler.getListOfContact(owner);

    for (auto it = contacts.cbegin(); it != contacts.cend(); ++it) {
        if (it->_name == username) {
            return true;
        }
    }
    return false;
}

int AsioTCPCli::acceptContact(const std::string &username)
{
    if (!this->_connected_user) {
        write(500, "You must be logged in"); // TODO: send real code
        return 1;
    }
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    User user = userHandler.getUser(username);

    if (user._exists) {
        if (!checkContactRequest(contactHandler, this->_connected_user->_name, username)) {
            write(500, "Request not found"); // TODO: send real code
            return 1;
        }
        contactHandler.acceptContactRequest(username, this->_connected_user->_name);
    }
    return 0;
}

int AsioTCPCli::denyContact(const std::string &username)
{
    if (!this->_connected_user) {
        write(500, "You must be logged in"); // TODO: send real code
        return 1;
    }
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    User user = userHandler.getUser(username);

    if (user._exists) {
        if (!checkContactRequest(contactHandler, username, this->_connected_user->_name)) {
            write(500, "Request not found"); // TODO: send real code
            return 1;
        }
        contactHandler.dismissContactRequest(this->_connected_user->_name, username);
    }
    return 0;
}

int AsioTCPCli::delContact(const std::string &username)
{
    if (!this->_connected_user) {
        write(500, "You must be logged in"); // TODO: send real code
        return 1;
    }
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    User user = userHandler.getUser(username);

    if (user._exists) {
        if (!checkContact(contactHandler, username, this->_connected_user->_name)) {
            write(500, "Contact not found"); // TODO: send real code
            return 1;
        }
        contactHandler.removeContact(this->_connected_user->_name, username);
    }
    return 0;
}

int AsioTCPCli::getContacts(const std::string &username)
{
    if (!this->_connected_user) {
        write(500, "You must be looged in");
        return 1;
    }
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    User user = userHandler.getUser(username);
    std::vector<Contact> contactsList;
    std::string data;

    if (user._exists) {
        contactsList = contactHandler.getListOfContact(user._name);
        for (auto &contact : contactsList) {
            data.append(contact._name);
            data.append(";");
        }
        write(206, data.c_str());
    }
    return 0;
}