/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** MyWindow
*/

#ifndef MYWINDOW_HPP_
#define MYWINDOW_HPP_

#include <QMainWindow>
#include <QMessageBox>

#include <QtWidgets/QStackedWidget>

#include <memory>

#include "CallHandler.hpp"
#include "ContactHandler.hpp"

#include "HomeScreen.hpp"
#include "LoginScreen.hpp"

class MyWindow : public QMainWindow
{
public:
    MyWindow();
    ~MyWindow();

private slots:
    void handleButton();

private:
    void init_buttons();

private:
    void setUp_winodw();
    void connect_buttons() noexcept;

private:
    //callback functions
    void on_login_button_clicked();
    void on_call_button_clicked();

private:
    std::unique_ptr<QStackedWidget> _stack;
    std::unique_ptr<HomeScreen> _home;
    std::unique_ptr<LoginScreen> _login;

    CallHandler _callHandler;
    ContactHandler _contactHandler;
};

#endif /* !MYWINDOW_HPP_ */
