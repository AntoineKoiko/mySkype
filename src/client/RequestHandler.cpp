/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** RequestHandler
*/

#include "RequestHandler.hpp"

RequestHandler::RequestHandler(const std::shared_ptr<Babel::Client::Network::TcpClient> client,
                               std::shared_ptr<UserHandler> userHandler, std::shared_ptr<ContactHandler> contactHandler, CallHandler &callHandler) : _client(client), _userHandler(userHandler), _contactHandler(contactHandler), _callHandler(callHandler)
{
    _requestMap[Babel::Res::CONNECTION_ACCEPTED] = &RequestHandler::onConnected;
    _requestMap[Babel::Res::LOGGED_IN] = &RequestHandler::onLoggedIn;
    _requestMap[Babel::Res::ACCEPT_CTC_REQ] = &RequestHandler::onContactRequestAccepted;
    _requestMap[Babel::Res::CONTACTS_LIST] = &RequestHandler::onGetContacts;
    _requestMap[Babel::Res::NEW_CONTACT_REQ] = &RequestHandler::onContactRequest;
    _requestMap[Babel::Res::CALL_ACCEPTED] = &RequestHandler::onCallAccepted;
    _requestMap[Babel::Res::JOIN_CALL] = &RequestHandler::onSomeoneJoin;
    _requestMap[Babel::Res::CALL_REQUEST] = &RequestHandler::onCallRequest;
    _requestMap[Babel::Res::BAD_REQUEST] = &RequestHandler::onBadRequest;
    QObject::connect(dynamic_cast<QObject *>(_client.get()), SIGNAL(newPacketReceive()), this, SLOT(onNewPacketReceive()));
}

RequestHandler::~RequestHandler()
{
}

std::vector<std::string> RequestHandler::splitString(const std::string &str, char separator) const
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
    if (dataPacket.magic != MAGIC_NUMBER)
    {
        std::cout << "Wrong magic number" << std::endl;
        return;
    }
    std::cout << "code:" << dataPacket.code << std::endl;
    std::cout << "content: " << dataPacket.data << std::endl;
    auto it = _requestMap.find(dataPacket.code);

    if (it != _requestMap.end())
    {
        (this->*(it->second))(dataPacket);
    }
    else
    {
        std::cout << "Impossible to find the command code: " << dataPacket.code << std::endl;
    }
}

void RequestHandler::onConnected(const DataPacket &packetReceive)
{
    std::cout << "Connected to server under ip: " << packetReceive.data << std::endl;
    _userHandler->setIpAddr(std::string(packetReceive.data));
}

void RequestHandler::onLoggedIn(const DataPacket &packetReceive)
{
    DataPacket packetSend;

    packetSend.code = 005;
    std::memcpy(packetSend.data, packetReceive.data, packetReceive.size);
    packetSend.size = packetReceive.size;
    this->_client->send(DataPacketManager::serialize(packetSend));
    emit this->loginConfirmed();
}

void RequestHandler::onContactRequestAccepted(const DataPacket &packetReceive)
{
    this->_contactHandler->addContact(std::string(packetReceive.data));
}

void RequestHandler::onGetContacts(const DataPacket &packetReceive)
{
    std::vector<std::string> contactList = this->splitString(std::string(packetReceive.data), ';');

    for (auto &contact : contactList)
    {
        this->_contactHandler->addContact(contact);
    }
}

void RequestHandler::onContactRequest(const DataPacket &packetReceive)
{
    this->_contactHandler->addContactRequest(packetReceive.data);
}

void RequestHandler::onCallAccepted(const DataPacket &packetReceive)
{
    std::string packetString(packetReceive.data);
    std::vector<std::string> usersCall;

    std::cout << "On call accept -> " << packetReceive.data << std::endl;
    if (packetString.find(";") != std::string::npos)
    {
        usersCall = this->splitString(std::string(packetReceive.data), ';');
    }
    else
    {
        usersCall.push_back(packetString);
    }
    for (const auto &userCall : usersCall)
    {
        std::vector<std::string> userParsed = this->splitString(userCall, ':');
        std::cout << "name -> " << userParsed[0] << " + ip -> " << userParsed[1] << std::endl;
        _callHandler.addPeopleOnCall(userParsed[0], userParsed[1]);
    }
    emit this->newCallAccepted();
}

void RequestHandler::onSomeoneJoin(const DataPacket &packetReceive)
{
    std::string content(packetReceive.data);
    std::vector<std::string> dataParsed = splitString(content, ':');

    _callHandler.addPeopleOnCall(dataParsed[0], dataParsed[1]);
    emit this->newCallJoining();
}

void RequestHandler::onCallRequest(const DataPacket &packetReceive)
{
    std::string content(packetReceive.data);
    std::vector<std::string> dataParsed = splitString(content, ':');

    //_callHandler.addPeopleOnCall(dataParsed[0], dataParsed[1]);
    _callHandler.setCallOwner(dataParsed[0]);
    emit this->newCallRequest();
}

void RequestHandler::onBadRequest(const DataPacket &packetReceive)
{
    std::cout << "Bad Request: " << packetReceive.data << std::endl;
}

#include "moc_RequestHandler.cpp"