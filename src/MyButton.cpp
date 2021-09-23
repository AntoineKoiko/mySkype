/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** MyButton
*/

#include "MyButton.hpp"

MyButton::MyButton(const QString &title, QWidget *parent)
    : QPushButton(title, parent)
{
}

MyButton::~MyButton()
{
}
