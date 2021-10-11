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
                                                                       _requestHandler(_client, _userHandler, _contactHandler)

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
}

MyWindow::~MyWindow()
{
}

void MyWindow::on_login_button_clicked()
{
    qDebug() << _login->getUsernameField()->text();
    if (_login->getUsernameField()->text().toStdString().size())
    {
        _userHandler->login(_login->getUsernameField()->text().toStdString());
        _home->setUsername(_login->getUsernameField()->text().toStdString());
        _login->getUsernameField()->clear();
        //_stack->setCurrentWidget(_home.get());
    }
}

void MyWindow::successLogin()
{
    _stack->setCurrentWidget(_home.get());
}

void MyWindow::on_call_button_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Call", "Are you sure to want to make a call?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        qDebug() << "Say Yes";
        std::vector<QString> contacts;
        QListWidget *callList = _home->get_toCallList();
        for (int i = 0; i < callList->count(); ++i)
        {
            QListWidgetItem *item = callList->item(i);
            contacts.push_back(item->text());
        }
        _callScreen->startCall(contacts);
        _callHandler.call("toto");
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

    if (contactUsername.size()) {
        _contactHandler->makeContactRequest(contactUsername);
    }
}
