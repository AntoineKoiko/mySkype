/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** AddContactWidget
*/

#include "AddContactWidget.hpp"

AddContactWidget::AddContactWidget() : QWidget(),
                                       _searchField(std::make_unique<QLineEdit>(this)),
                                       _addButton(std::make_unique<QPushButton>(this)),
                                       _confirmationLabel(std::make_unique<QLabel>(this))
{
    _addButton->setText("Add");
    _searchField->setPlaceholderText("Contact name");
    _confirmationLabel->setText("contact added");
}

AddContactWidget::~AddContactWidget()
{
}

QLineEdit *AddContactWidget::get_searchField() const noexcept
{
    return _searchField.get();
}

QPushButton *AddContactWidget::get_addButton() const noexcept
{
    return _addButton.get();
}

QLabel *AddContactWidget::get_label() const noexcept
{
    return _confirmationLabel.get();
}

QString AddContactWidget::getFieldContent() const noexcept
{
    return _searchField->text();
}

void AddContactWidget::clearField() noexcept
{
    _searchField->clear();
}
