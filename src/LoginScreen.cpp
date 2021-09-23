/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** LoginScreen
*/

#include "LoginScreen.hpp"

LoginScreen::LoginScreen() : QWidget(),
                             _usernameFiel(new QLineEdit(this)),
                             _welcomeText(new QLabel(this))
{
    _welcomeText->setText("Welcome on Babel VOIP Application!");
    _welcomeText->move(100, 100);

    _usernameFiel->move(100, 200);
    _usernameFiel->setPlaceholderText("Username");

    _welcomeText->show();
    _usernameFiel->show();
}

LoginScreen::~LoginScreen()
{
}
