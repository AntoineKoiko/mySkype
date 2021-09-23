/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** LoginScreen
*/

#ifndef LOGINSCREEN_HPP_
#define LOGINSCREEN_HPP_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class LoginScreen : public QWidget
{
public:
    LoginScreen();
    ~LoginScreen();

private:
    QLabel *_welcomeText;
    QLineEdit *_usernameFiel;
};

#endif /* !LOGINSCREEN_HPP_ */
