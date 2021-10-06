/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AddContactWidget
*/

#ifndef ADDCONTACTWIDGET_HPP_
#define ADDCONTACTWIDGET_HPP_

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include <memory>

class AddContactWidget : public QWidget
{
public:
    AddContactWidget();
    ~AddContactWidget();

    QLineEdit *get_searchField() const noexcept;
    QPushButton *get_addButton() const noexcept;
    QLabel *get_label() const noexcept;

    //field = LineEdit
    QString getFieldContent() const noexcept;
    void clearField() noexcept;

private:
    std::unique_ptr<QLineEdit> _searchField;
    std::unique_ptr<QPushButton> _addButton;
    std::unique_ptr<QLabel> _confirmationLabel;
};

#endif /* !ADDCONTACTWIDGET_HPP_ */
