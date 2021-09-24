/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** HomeScreen
*/

#ifndef HOMESCREEN_HPP_
#define HOMESCREEN_HPP_

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QBoxLayout>
#include <QPushButton>

#include <vector>

class HomeScreen : public QWidget
{
public:
    HomeScreen();
    ~HomeScreen();

private:
    void on_addToCallButton_clicked();
    void on_cancelToCallButton_clicked();

private:
    QListWidget *_contactsList;
    QListWidget *_toCallList;

    QLineEdit *_searchContactField;
    QPushButton *_addToCallButton;
    QPushButton *_cancelToCallButton;

    QVBoxLayout *_vLayout;
    QGridLayout *_mainLayout;
};

#endif /* !HOMESCREEN_HPP_ */
