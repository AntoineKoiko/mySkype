/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** LoginScreen
*/

#include "LoginScreen.hpp"
#include <QFont>

LoginScreen::LoginScreen(QWidget *parent) : QWidget(parent),
                                            _usernameField(std::make_unique<QLineEdit>(this)),
                                            _welcomeText(std::make_unique<QLabel>(this)),
                                            _loginButton(std::make_unique<QPushButton>(this)),
                                            _layout(std::make_unique<QVBoxLayout>())
{
    _welcomeText->setText("Welcome on Babel VOIP Application!");
    _welcomeText->move(100, 100);
    _welcomeText->setAlignment(Qt::AlignCenter);
    _welcomeText->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    _welcomeText->setFont(QFont("Arial", 24, QFont::Bold));

    _usernameField->move(100, 200);
    _usernameField->setPlaceholderText("Username");

    _loginButton->move(100, 300);
    _loginButton->setText("login");

    _layout->addWidget(_welcomeText.get(), Qt::AlignCenter);
    _layout->addWidget(_usernameField.get(), Qt::AlignCenter);
    _layout->addWidget(_loginButton.get(), Qt::AlignCenter);

    setLayout(_layout.get());

    this->setStyleSheet("background-color:black;color:white");
}
#include <iostream>
LoginScreen::~LoginScreen()
{
    std::cout << "login" << std::endl;
}

QPushButton *LoginScreen::get_login_button() const noexcept
{
    return _loginButton.get();
}

QLineEdit *LoginScreen::get_username_field() const noexcept
{
    return _usernameField.get();
}
