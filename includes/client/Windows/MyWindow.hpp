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
#include "CallScreen.hpp"
#include "UserHandler.hpp"
#include "TcpClient.hpp"
#include "RequestHandler.hpp"

class MyWindow : public QMainWindow
{
public:
    MyWindow(const std::shared_ptr<UserHandler> userHandler, const std::shared_ptr<Babel::Client::Network::TcpClient> client);
    ~MyWindow();

private slots:
    void handleButton();
    void successLogin();

private:
    void init_buttons();

private:
    void setUp_winodw();
    void connect_buttons() noexcept;

private:
    //callback functions
    void on_login_button_clicked();
    void on_call_button_clicked();
    void on_hangUp_button_clicked();
    void on_acceptContactRequest_button_clicked();
    void on_dismissContactRequest_button_clicked();
    void on_addContactRequest_button_clicked();
    void onCallRequest();

private:
    std::unique_ptr<QStackedWidget> _stack;
    std::unique_ptr<HomeScreen> _home;
    std::unique_ptr<LoginScreen> _login;
    std::unique_ptr<CallScreen> _callScreen;
    std::shared_ptr<Babel::Client::Network::TcpClient> _client;
    std::shared_ptr<UserHandler> _userHandler;
    std::shared_ptr<ContactHandler> _contactHandler;
    CallHandler _callHandler;
    RequestHandler _requestHandler;

};

#endif /* !MYWINDOW_HPP_ */
