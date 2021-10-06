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

MyWindow::MyWindow() : QMainWindow(),
                       _stack(std::make_unique<QStackedWidget>()),
                       _home(std::make_unique<HomeScreen>(_stack.get())),
                       _login(std::make_unique<LoginScreen>(_stack.get())),
                       _callScreen(std::make_unique<CallScreen>(_stack.get())),
                       _contactHandler(_home->getContactList(), _home->getContactRequestList())

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
    connect(_login->get_login_button(), &QPushButton::released,
            this, &MyWindow::on_login_button_clicked);
    connect(_home->get_call_button(), &QPushButton::released,
            this, &MyWindow::on_call_button_clicked);
    connect(_home->getAcceptContactButton(), &QPushButton::released,
            this, &MyWindow::on_acceptContactRequest_button_clicked);
    connect(_home->getDismissContactButton(), &QPushButton::released,
            this, &MyWindow::on_dismissContactRequest_button_clicked);
    connect(_home->getAddContactButton(), &QPushButton::released,
            this, &MyWindow::on_addContactRequest_button_clicked);
    connect(_callScreen->get_hangUp_button(), &QPushButton::released,
            this, &MyWindow::on_hangUp_button_clicked);
}

MyWindow::~MyWindow()
{
}

void MyWindow::on_login_button_clicked()
{
    qDebug() << _login->get_username_field()->text();
    _login->get_username_field()->clear();
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
        _callScreen->start_call(contacts);
        _callHandler.make_call("toto");
        _stack->setCurrentWidget(_callScreen.get());
    }
    else
    {
        qDebug() << "Say no";
    }
}

void MyWindow::on_hangUp_button_clicked()
{
    _callScreen->stop_call();
    _stack->setCurrentWidget(_home.get());
}

void MyWindow::on_acceptContactRequest_button_clicked()
{
    _contactHandler.acceptContactRequest();
}

void MyWindow::on_dismissContactRequest_button_clicked()
{
    _contactHandler.dismissContactRequest();
}

void MyWindow::on_addContactRequest_button_clicked()
{
    std::string contactUsername = _home->getAddContactWidget()->getFieldContent().toStdString();
    _home->getAddContactWidget()->clearField();

    _contactHandler.makeContactRequest(contactUsername);
}
