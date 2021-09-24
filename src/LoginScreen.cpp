/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** LoginScreen
*/

#include "LoginScreen.hpp"

LoginScreen::LoginScreen() : QWidget(),
                             _usernameField(new QLineEdit(this)),
                             _welcomeText(new QLabel(this)),
                             _loginButton(new QPushButton(this)),
                             _layout(new QVBoxLayout)
{
    _welcomeText->setText("Welcome on Babel VOIP Application!");
    _welcomeText->move(100, 100);

    _usernameField->move(100, 200);
    _usernameField->setPlaceholderText("Username");

    _loginButton->move(100, 300);
    _loginButton->setText("login");

    _layout->addWidget(_welcomeText, 1);
    _layout->addWidget(_usernameField, 1);
    _layout->addWidget(_loginButton, 1);

    setLayout(_layout);
    // _loginButton->show();
    // _welcomeText->show();
    // _usernameField->show();
}

LoginScreen::~LoginScreen()
{
}

QPushButton *LoginScreen::get_login_button() const noexcept
{
    return _loginButton;
}

QLineEdit *LoginScreen::get_username_field() const noexcept
{
    return _usernameField;
}
