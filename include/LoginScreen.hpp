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
#include <QPushButton>
#include <QBoxLayout>

class LoginScreen : public QWidget
{
public:
    LoginScreen();
    ~LoginScreen();

    QPushButton *get_login_button() const noexcept;
    QLineEdit *get_username_field() const noexcept;

private:
    QLabel *_welcomeText;
    QLineEdit *_usernameField;
    QPushButton *_loginButton;

    QVBoxLayout *_layout;
};

#endif /* !LOGINSCREEN_HPP_ */
