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
        client.write(207, it->_name.c_str());
    }
}

int AsioTCPCli::login(const std::string &username)
{
    std::cout << "Client : " << this->get_ip_string() << " trying to log in as " << username << std::endl;
    auto serv = get_server();
    auto userHandler = serv->getUserHandler();
    auto contactHandler = serv->getContactHandler();
    User user = userHandler.getUser(username);

    if (user._exists) {
        this->_connected_user = std::make_shared<User>(user);
        write(201, username.c_str());
        sendAllRequests(this->_connected_user->_name, contactHandler, *this);
    } else {
        serv->getUserHandler().addUser(username);
        user = userHandler.getUser(username);
        if (serv->getServer().isUserLogged(username)) {
            write(401, username.c_str());
            return 1;
        }
        this->_connected_user = std::make_shared<User>(user);
        write(201, username.c_str());
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
        write(500, "Not Connected"); // TODO: change for real code
        return 1;
    }
    contactHandler.addContactRequest(owner, username);
    if (user_client)
        user_client->write(207, owner.c_str());
    return 0;
}

static bool checkContactRequest(const ContactHandler *handler, const std::string &username, const std::string &owner)
{
    auto ownerRequests = handler->getListOfContactRequest(owner);

    for (auto it = ownerRequests.cbegin(); it != ownerRequests.cend(); ++it) {
        if (it->_name == username) {
            return true;
        }
    }
    return false;
}

int AsioTCPCli::addContact(const std::string &username)
{
    // TODO: accept contact request
    if (!this->_connected_user) {
        write(500, "You must be logged in");
        return 1;
    }
    auto serv = get_server();
    auto contactHandler = serv->getContactHandler();
    auto userHandler = serv->getUserHandler();
    User user = userHandler.getUser(username);

    if (user._exists) {
        if (!checkContactRequest(contactHandler, username, this->_connected_user->_name)) {
            write(500, "Request not found");
            return 1;
        }
        contactHandler.acceptContactRequest(this->_connected_user->_name, username);
    }
    return 0;
}