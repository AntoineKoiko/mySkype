/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** HomeScreen
*/

#include "HomeScreen.hpp"

HomeScreen::HomeScreen() : QWidget(),
                           _homeText(new QLabel("Hello", this)),
                           _contactsList(new QListWidget(this))
{
    _contactsList->setMaximumHeight(800);
    _contactsList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for (int i = 0; i < 20; i++)
    {
        _contactsList->addItem(QString::number(i));
    }
}

HomeScreen::~HomeScreen()
{
}
