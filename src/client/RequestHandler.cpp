/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** RequestHandler
*/

#include "RequestHandler.hpp"

RequestHandler::RequestHandler(const std::shared_ptr<Babel::Client::Network::TcpClient> client,
                               std::shared_ptr<UserHandler> userHandler, std::shared_ptr<ContactHandler> contactHandler) : _client(client), _userHandler(userHandler), _contactHandler(contactHandler)
{
    QObject::connect(dynamic_cast<QObject *>(_client.get()), SIGNAL(newPacketReceive()), this, SLOT(onNewPacketReceive()));
}

RequestHandler::~RequestHandler()
{
}

std::vector<std::string> RequestHandler::split_string(const std::string &str, char separator) const
{
    std::vector<std::string> ret;
    std::size_t i = 0;

    while (i != str.size())
    {
        while (i != str.size() && str.c_str()[i] == separator)
            ++i;
        std::size_t j = i;
        while (j != str.size() && str.c_str()[j] != separator)
        {
            j++;
        }
        if (i != j)
        {
            ret.push_back(str.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

void RequestHandler::onNewPacketReceive()
{
    std::vector<char> data = this->_client->getData();
    DataPacket dataPacket = DataPacketManager::deserialize(data);

    std::cout << "On receive un nouveau packet via RequestHandler" << std::endl;
    if (dataPacket.code == 207)
    {
        this->_contactHandler->addContactRequest(dataPacket.data);
    }
    if (dataPacket.code == 206) {
        std::vector<std::string> contactList = this->split_string(std::string(dataPacket.data), ';');
        for (auto &contact : contactList) {
            this->_contactHandler->addContact(contact);
        }
    }
    if (dataPacket.code == 201) {
        DataPacket packetSend;

        packetSend.code = 005;
        std::memcpy(packetSend.data, dataPacket.data, dataPacket.size);
        packetSend.size = dataPacket.size;
        this->_client->send(DataPacketManager::serialize(packetSend));
    }
    //this->_contactHandler->dism
    std::cout << "code:" << dataPacket.code << std::endl;
    std::cout << "content: " << dataPacket.data << std::endl;
}

#include "moc_RequestHandler.cpp"