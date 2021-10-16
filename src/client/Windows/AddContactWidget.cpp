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
    _confirmationLabel->setText("");
}

AddContactWidget::~AddContactWidget()
{
}

QLineEdit *AddContactWidget::getSearchField() const noexcept
{
    return _searchField.get();
}

QPushButton *AddContactWidget::getAddButton() const noexcept
{
    return _addButton.get();
}

QLabel *AddContactWidget::getLabel() const noexcept
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

void AddContactWidget::showContactNameUnknown() const noexcept
{
    _confirmationLabel->setStyleSheet("color:red;");
    _confirmationLabel->setText("Contact Request Failed!");
}

#include <iostream>

void AddContactWidget::showRequestSended() const noexcept
{
    std::cout << "show request sended" << std::endl;
    _confirmationLabel->setStyleSheet("color:green;");
    _confirmationLabel->setText("Contact request transmited!");
}
