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

#include <memory>
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
    std::unique_ptr<QListWidget> _contactsList;
    std::unique_ptr<QListWidget> _toCallList;
    std::unique_ptr<QListWidget> _newContactList;

    std::unique_ptr<QLabel> _contactAddedLabel;
    std::unique_ptr<QLabel> _contactListLabel;
    std::unique_ptr<QLabel> _callListLabel;
    std::unique_ptr<QLabel> _pendingLIstLabel;

    std::unique_ptr<QLineEdit> _searchContactField;
    std::unique_ptr<QPushButton> _addToCallButton;
    std::unique_ptr<QPushButton> _cancelToCallButton;
    std::unique_ptr<QPushButton> _addContactButton;
    std::unique_ptr<QPushButton> _dismissContactButton;
    std::unique_ptr<QPushButton> _acceptContactButton;
    std::unique_ptr<QPushButton> _callButton;

    std::unique_ptr<QGridLayout> _mainLayout;
};

#endif /* !HOMESCREEN_HPP_ */
