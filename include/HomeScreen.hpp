/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** HomeScreen
*/

#ifndef HOMESCREEN_HPP_
#define HOMESCREEN_HPP_

#include <QWidget>
#include <QLabel>

class HomeScreen : public QWidget
{
public:
    HomeScreen();
    ~HomeScreen();

private:
    QLabel *_homeText;
};

#endif /* !HOMESCREEN_HPP_ */
