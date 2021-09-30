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
                       _login(std::make_unique<LoginScreen>((_stack.get())))

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
    _stack->setCurrentWidget(_login.get());
    setCentralWidget(_stack.get());
}

void MyWindow::connect_buttons() noexcept
{
    connect(_login->get_login_button(), &QPushButton::released,
            this, &MyWindow::on_login_button_clicked);
    connect(_home->get_call_button(), &QPushButton::released,
            this, &MyWindow::on_call_button_clicked);
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
    }
    else
    {
        qDebug() << "Say no";
    }

    qDebug()
        << "call";
    QListWidget *callList = _home->get_toCallList();
    for (int i = 0; i < callList->count(); ++i)
    {
        QListWidgetItem *item = callList->item(i);
        qDebug() << item->text();
    }

    _callHandler.make_call("toto");
}