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
    this->setUp_winodw();

    connect_buttons();
}

void MyWindow::setUp_winodw()
{
    resize(1200, 800);
    setWindowTitle("Babel");

    _stack->addWidget(_login.get());
    _stack->addWidget(_home.get());
    _stack->addWidget(_callScreen.get());
    _stack->setCurrentWidget(_login.get());

    setCentralWidget(_stack.get());
}

void MyWindow::connect_buttons() noexcept
{
    connect(_login->getLoginButton(), &QPushButton::released,
            this, &MyWindow::on_login_button_clicked);
    connect(_home->get_call_button(), &QPushButton::released,
            this, &MyWindow::on_call_button_clicked);
    connect(_home->getAcceptContactButton(), &QPushButton::released,
            this, &MyWindow::on_acceptContactRequest_button_clicked);
    connect(_home->getDismissContactButton(), &QPushButton::released,
            this, &MyWindow::on_dismissContactRequest_button_clicked);
    connect(_home->getAddContactButton(), &QPushButton::released,
            this, &MyWindow::on_addContactRequest_button_clicked);
    connect(_callScreen->getHangUpButton(), &QPushButton::released,
            this, &MyWindow::on_hangUp_button_clicked);
    connect(&_requestHandler, &RequestHandler::loginConfirmed, this, &MyWindow::successLogin);
    connect(&_requestHandler, &RequestHandler::newCallRequest, this, &MyWindow::onCallRequest);
}

MyWindow::~MyWindow()
{
}

void MyWindow::on_login_button_clicked()
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
    //_stack->setCurrentWidget(_home.get());
}

void MyWindow::successLogin()
{
    _stack->setCurrentWidget(_home.get());
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

void MyWindow::on_call_button_clicked()
{
    bool confirm_call = false;
    std::vector<std::string> peoplesOnCall;

    if (!_home->get_toCallList()->count())
    {
        return;
    }
    confirm_call = Modal::YesNo(this, QString("Call"),
                                QString("Are you sure to want to make a call?"));

    if (confirm_call)
    {
        qDebug() << "Say Yes";
        std::vector<QString> contacts(_home->get_toCallList()->getQStrItems());
        _callScreen->startCall(contacts);
        _callHandler.call(peoplesOnCall, _userHandler->getIpAddr());
        _stack->setCurrentWidget(_callScreen.get());
    }
    else
    {
        qDebug() << "Say no";
    }
}

void MyWindow::on_hangUp_button_clicked()
{
    _callScreen->stopCall();
    _callHandler.hangup();
    _stack->setCurrentWidget(_home.get());
}

void MyWindow::on_acceptContactRequest_button_clicked()
{
    _contactHandler->acceptContactRequest();
}

void MyWindow::on_dismissContactRequest_button_clicked()
{
    _contactHandler->dismissContactRequest();
}

void MyWindow::on_addContactRequest_button_clicked()
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
