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

void RequestHandler::onNewPacketReceive()
{
    std::vector<char> data = this->_client->getData();
    DataPacket dataPacket = DataPacketManager::deserialize(data);

    std::cout << "On receive un nouveau packet via RequestHandler" << std::endl;
    if (dataPacket.code == 207) {
        this->_contactHandler->addContactRequest(dataPacket.data);
    }
    //this->_contactHandler->dism
    std::cout << "code:" << dataPacket.code << std::endl;
    std::cout << "content: " << dataPacket.data << std::endl;
}

#include "moc_RequestHandler.cpp"