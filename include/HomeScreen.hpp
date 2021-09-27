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
#include <QLabel>

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
    QListWidget *_newContactList;

    QLabel *_contactAddedLabel;
    QLabel *_contactListLabel;
    QLabel *_callListLabel;
    QLabel *_pendingLIstLabel;

    QLineEdit *_searchContactField;
    QPushButton *_addToCallButton;
    QPushButton *_cancelToCallButton;
    QPushButton *_addContactButton;
    QPushButton *_dismissContactButton;
    QPushButton *_acceptContactButton;
    QPushButton *_callButton;

    QGridLayout *_mainLayout;
};

#endif /* !HOMESCREEN_HPP_ */
