/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** HomeScreen
*/

#include "HomeScreen.hpp"

HomeScreen::HomeScreen() : QWidget(),
                           _homeText(new QLabel("Hello", this))
{
}

HomeScreen::~HomeScreen()
{
}
