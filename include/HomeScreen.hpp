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

#include "TitledListWithButton.hpp"

#include <memory>
#include <vector>

class HomeScreen : public QWidget
{
public:
    HomeScreen();
    ~HomeScreen();

    QPushButton *get_call_button() const noexcept;

private:
    //buttons callback
    void on_addToCallButton_clicked();
    void on_cancelToCallButton_clicked();

    //setup
    void setUp_widget() noexcept;
    void connect_buttons() noexcept;
    void setup_layout() noexcept;

private:
    std::unique_ptr<QListWidget> _newContactList;

    std::unique_ptr<QLabel> _contactAddedLabel;
    std::unique_ptr<QLabel> _pendingLIstLabel;

    std::unique_ptr<QLineEdit> _searchContactField;
    std::unique_ptr<QPushButton> _addContactButton;
    std::unique_ptr<QPushButton> _dismissContactButton;
    std::unique_ptr<QPushButton> _acceptContactButton;
    std::unique_ptr<QPushButton> _callButton;

    std::unique_ptr<TitledListWithButton> _contactWidget;
    std::unique_ptr<TitledListWithButton> _toCallWidget;

    std::unique_ptr<QGridLayout> _mainLayout;
};

#endif /* !HOMESCREEN_HPP_ */
