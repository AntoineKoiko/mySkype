/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** MyButton
*/

#ifndef MYBUTTON_HPP_
#define MYBUTTON_HPP_

#include <QPushButton>
#include <QWidget>
#include <QString>
#include <string>

class MyButton : QPushButton
{
public:
    MyButton(const QString &title, QWidget *parent = nullptr);
    ~MyButton();

protected:
private:
};

#endif /* !MYBUTTON_HPP_ */
