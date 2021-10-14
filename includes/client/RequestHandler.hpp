/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** RequestHandler
*/

#ifndef REQUESTHANDLER_HPP_
#define REQUESTHANDLER_HPP_

#include <QObject>
#include "TcpClient.hpp"
#include "ContactHandler.hpp"
#include "UserHandler.hpp"
#include "CallHandler.hpp"
#include <vector>
#include <string>

class RequestHandler : public QObject
{
    Q_OBJECT

    typedef void (RequestHandler::*req)(const DataPacket &);

public:
    RequestHandler(const std::shared_ptr<Babel::Client::Network::TcpClient> client,
                   std::shared_ptr<UserHandler> userHandler, std::shared_ptr<ContactHandler> contactHandler,
                   CallHandler &callHandler);
    ~RequestHandler();

    std::vector<std::string> split_string(const std::string &str, char separator) const;

signals:
    void loginConfirmed();
    void newCallRequest();

private slots:
    void onNewPacketReceive();

protected:
private:
    void onConnected(const DataPacket &); //200
    void onLoggedIn(const DataPacket &); //201
    void onContactRequestAccepted(const DataPacket &); //203
    void onGetContacts(const DataPacket &); //206
    void onContactRequest(const DataPacket &); //207
    void onCallAccepted(const DataPacket &); //209
    void onSomeoneJoin(const DataPacket &); //210
    void onCallRequest(const DataPacket &); //211
    void onBadRequest(const DataPacket &); //400

    std::shared_ptr<Babel::Client::Network::TcpClient> _client;
    std::shared_ptr<UserHandler> _userHandler;
    std::shared_ptr<ContactHandler> _contactHandler;
    CallHandler &_callHandler;
    std::map<int, req> _requestMap;
};

#endif /* !REQUESTHANDLER_HPP_ */
