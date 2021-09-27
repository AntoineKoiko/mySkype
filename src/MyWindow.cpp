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

MyWindow::MyWindow() : QMainWindow(),
                       _home(std::make_unique<HomeScreen>()),
                       _login(std::make_unique<LoginScreen>())

{
    resize(1200, 800);
    setWindowTitle("Babel");

    connect_buttons();

    setCentralWidget(_login.get());
}

MyWindow::~MyWindow()
{
}
#include <memory>
void MyWindow::connect_buttons() noexcept
{
    connect(_login->get_login_button(), &QPushButton::clicked,
            this, &MyWindow::on_login_button_clicked);
}

void MyWindow::on_login_button_clicked()
{
    qDebug() << _login->get_username_field()->text();
    _login->get_username_field()->clear();
    setCentralWidget(_home.get());
}
