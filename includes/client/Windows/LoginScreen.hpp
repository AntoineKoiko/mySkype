/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** LoginScreen
*/

#ifndef LOGINSCREEN_HPP_
#define LOGINSCREEN_HPP_

#include <QMessageBox>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>

#include <memory>

class LoginScreen : public QWidget
{
public:
    explicit LoginScreen(QWidget *parent);
    ~LoginScreen();

    QPushButton *getLoginButton() const noexcept;
    QLineEdit *getUsernameField() const noexcept;

    void showBadCharError() const noexcept;
    void showMissingCharError() const noexcept;
    void showEmptyUsernameError() const noexcept;

private:
    std::unique_ptr<QLabel> _welcomeText;
    std::unique_ptr<QLabel> _errorLabel;
    std::unique_ptr<QLineEdit> _usernameField;
    std::unique_ptr<QPushButton> _loginButton;

    std::unique_ptr<QVBoxLayout> _layout;
};

#endif /* !LOGINSCREEN_HPP_ */
