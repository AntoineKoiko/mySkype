/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** MyWindow
*/

#include "MyWindow.hpp"
#include <iostream>
#include <QDebug>
#include <QtWidgets/QStackedWidget>
#include <QListWidget>

MyWindow::MyWindow() : QMainWindow(),
                       _home(std::make_unique<HomeScreen>()),
                       _login(std::make_unique<LoginScreen>())

{
    this->setUp_winodw();

    connect_buttons();
}

void MyWindow::setUp_winodw()
{
    resize(1200, 800);
    setWindowTitle("Babel");
    setCentralWidget(_login.get());
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
    setCentralWidget(_home.get());
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