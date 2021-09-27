/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** MyWindow
*/

#ifndef MYWINDOW_HPP_
#define MYWINDOW_HPP_

#include <memory>
#include <QApplication>
#include <QPushButton>
#include <vector>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>

#include <memory>

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
    void connect_buttons() noexcept;

private:
    void on_login_button_clicked();
    void on_call_button_clicked();

private:
    std::unique_ptr<HomeScreen> _home;
    std::unique_ptr<LoginScreen> _login;
};

#endif /* !MYWINDOW_HPP_ */
