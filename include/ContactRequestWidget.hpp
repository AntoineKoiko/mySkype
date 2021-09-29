/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** ContactRequestWidget
*/

#ifndef CONTACTREQUESTWIDGET_HPP_
#define CONTACTREQUESTWIDGET_HPP_

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>

#include <memory>

class ContactRequestWidget : public QWidget
{
public:
    ContactRequestWidget();
    ~ContactRequestWidget();

    QLabel *get_title() const noexcept;
    QListWidget *get_requestsList() const noexcept;
    QPushButton *get_acceptButton() const noexcept;
    QPushButton *get_dismissButton() const noexcept;

private:
    std::unique_ptr<QLabel> _title;
    std::unique_ptr<QListWidget> _requestsList;
    std::unique_ptr<QPushButton> _acceptButton;
    std::unique_ptr<QPushButton> _dismissButton;
};

#endif /* !CONTACTREQUESTWIDGET_HPP_ */
