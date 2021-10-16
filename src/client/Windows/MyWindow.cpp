/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** MyWindow
*/

#include "MyWindow.hpp"
#include <iostream>
#include <QDebug>
#include <QListWidget>

#include "Modal.hpp"
#include "InputChecker.hpp"

using namespace Babel::Client;

MyWindow::MyWindow(const std::shared_ptr<UserHandler> userHandler,
                   const std::shared_ptr<Network::TcpClient> client) : QMainWindow(),
                                                                       _stack(std::make_unique<QStackedWidget>()),
                                                                       _home(std::make_unique<HomeScreen>(_stack.get())),
                                                                       _login(std::make_unique<LoginScreen>(_stack.get())),
                                                                       _callScreen(std::make_unique<CallScreen>(_stack.get())),
                                                                       _client(client),
                                                                       _userHandler(userHandler),
                                                                       _contactHandler(std::make_shared<ContactHandler>(_home->getContactList(), _home->getContactRequestList(), client)),
                                                                       _callHandler(client),
                                                                       _requestHandler(_client, _userHandler, _contactHandler, _callHandler)

{
    setUpWindow();
    connectButtons();
}

void MyWindow::setUpWindow()
{
    resize(1200, 800);
    setWindowTitle("Babel");

    _stack->addWidget(_login.get());
    _stack->addWidget(_home.get());
    _stack->addWidget(_callScreen.get());
    _stack->setCurrentWidget(_login.get());

    setCentralWidget(_stack.get());
}

void MyWindow::connectButtons() noexcept
{
    connect(_login->getLoginButton(), &QPushButton::released,
            this, &MyWindow::onLoginButtonClicked);
    connect(_home->getCallButton(), &QPushButton::released,
            this, &MyWindow::onCallButtonClicked);
    connect(_home->getAcceptContactButton(), &QPushButton::released,
            this, &MyWindow::onAcceptContactRequestButtonClicked);
    connect(_home->getDismissContactButton(), &QPushButton::released,
            this, &MyWindow::onDismissContactRequestButtonClicked);
    connect(_home->getAddContactButton(), &QPushButton::released,
            this, &MyWindow::onAddContactRequestButtonClicked);
    connect(_callScreen->getHangUpButton(), &QPushButton::released,
            this, &MyWindow::onHangUpButtonClicked);
    connect(&_requestHandler, &RequestHandler::loginConfirmed, this, &MyWindow::successLogin);
    connect(&_requestHandler, &RequestHandler::newCallRequest, this, &MyWindow::onCallRequest);
    connect(&_requestHandler, &RequestHandler::newCallAccepted, this, &MyWindow::onCallAccepted);
    connect(&_requestHandler, &RequestHandler::newCallJoining, this, &MyWindow::onSomeoneJoined);
    connect(&_requestHandler, &RequestHandler::contactRequestSucceed, this, &MyWindow::makeContactRequestSucceed);
    connect(&_requestHandler, &RequestHandler::contactRequestFailed, this, &MyWindow::makeContactRequestFailed);
}

MyWindow::~MyWindow()
{
}

void MyWindow::onLoginButtonClicked()
{
    qDebug() << _login->getUsernameField()->text();
    std::string username = _login->getUsernameField()->text().toStdString();

    if (username.empty())
    {
        _login->showEmptyUsernameError();
        return;
    }

    int check = InputChecker::checkLoginInput(username);

    if (check == 1)
    {
        _login->showBadCharError();
        return;
    }

    if (check == 2)
    {
        _login->showMissingCharError();
        return;
    }

    _userHandler->login(username);
    _home->setUsername(username);
    _login->getUsernameField()->clear();
}

void MyWindow::successLogin()
{
    _stack->setCurrentWidget(_home.get());
}

void MyWindow::makeContactRequestSucceed()
{
    std::cout << "show request sended in MyWindow" << std::endl;

    _home->contaactRequestSucceed();
}

void MyWindow::makeContactRequestFailed()
{
    _home->contactRequestFailed();
}

void MyWindow::onCallRequest()
{
    DataPacket callPacket;
    bool confirm_call = false;
    QString boxContent("Do you want to accept call from ");

    boxContent.append(this->_callHandler.getCallOwner().c_str());
    boxContent.append(" ?");
    confirm_call = Modal::YesNo(this, QString("Call"), boxContent);

    if (confirm_call)
    {
        callPacket.code = Babel::Req::ACCEPT_CALL;
        _client->send(DataPacketManager::serialize(callPacket));
        std::cout << "call accepted" << std::endl;
        _callScreen->startCall(std::vector<QString>());
        _stack->setCurrentWidget(_callScreen.get());
        _callHandler.acceptCall(_userHandler->getIpAddr());
    }
    else
    {
        callPacket.code = Babel::Req::REJECT_CALL;
        _client->send(DataPacketManager::serialize(callPacket));
        std::cout << "call refused" << std::endl;
    }
}

void MyWindow::onCallAccepted()
{
    std::vector<std::tuple<std::string, std::string>> peopleConnected = _callHandler.getConnectedPeople();
    std::vector<QString> peopleConnectedAsQString = {};

    for (auto &people : peopleConnected)
    {
        peopleConnectedAsQString.push_back(QString::fromStdString(std::get<1>(people)));
    }
    _callScreen->startCall(peopleConnectedAsQString);
}

void MyWindow::onSomeoneJoined()
{
    std::vector<std::tuple<std::string, std::string>> peopleConnected = _callHandler.getConnectedPeople();
    std::vector<QString> peopleConnectedAsQString = {};

    for (auto &people : peopleConnected)
    {
        peopleConnectedAsQString.push_back(QString::fromStdString(std::get<1>(people)));
    }
    _callScreen->startCall(peopleConnectedAsQString);
}

void MyWindow::onCallButtonClicked()
{
    bool confirm_call = false;
    std::vector<std::string> peoplesOnCall;

    if (!_home->getToCallList()->count())
    {
        return;
    }
    confirm_call = Modal::YesNo(this, QString("Call"),
                                QString("Are you sure to want to make a call?"));

    if (confirm_call)
    {
        qDebug() << "Say Yes";
        std::vector<QString> contacts;
        QListWidget *callList = _home->getToCallList();
        for (int i = 0; i < callList->count(); ++i)
        {
            QListWidgetItem *item = callList->item(i);
            contacts.push_back(item->text());
            peoplesOnCall.push_back(item->text().toStdString());
        }
        _callScreen->startCall(std::vector<QString>());
        _callHandler.call(peoplesOnCall, _userHandler->getIpAddr());
        _stack->setCurrentWidget(_callScreen.get());
    }
    else
    {
        qDebug() << "Say no";
    }
}

void MyWindow::onHangUpButtonClicked()
{
    DataPacket packet;

    packet = DataPacketManager::createPacket(103, std::string{""});
    _callScreen->stopCall();
    _callHandler.hangup();
    _client->send(DataPacketManager::serialize(packet));
    _callScreen->stopCall();
    _stack->setCurrentWidget(_home.get());
}

void MyWindow::onAcceptContactRequestButtonClicked()
{
    _contactHandler->acceptContactRequest();
}

void MyWindow::onDismissContactRequestButtonClicked()
{
    _contactHandler->dismissContactRequest();
}

void MyWindow::onAddContactRequestButtonClicked()
{
    std::string contactUsername = _home->getAddContactWidget()->getFieldContent().toStdString();
    _home->getAddContactWidget()->clearField();

    if (contactUsername.empty())
        return;

    int check = InputChecker::checkLoginInput(contactUsername);
    if (check == 1)
    {
        std::cerr << "ivnalid char" << std::endl;
        return;
    }
    if (check == 2)
    {
        std::cerr << "need at least one letter" << std::endl;
        return;
    }
    _contactHandler->makeContactRequest(contactUsername);
}
