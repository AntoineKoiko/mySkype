/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** ContactRequestWidget
*/

#include "ContactRequestWidget.hpp"

ContactRequestWidget::ContactRequestWidget() : QWidget(),
                                               _title(std::make_unique<QLabel>(this)),
                                               _requestsList(std::make_unique<ListStrWidget>(this)),
                                               _acceptButton(std::make_unique<QPushButton>(this)),
                                               _dismissButton(std::make_unique<QPushButton>(this))
{
    _title->setText("Pending \'Add Contact\' requests");
    _acceptButton->setText("Accept contact");
    _dismissButton->setText("Dismiss Contact");
}

ContactRequestWidget::~ContactRequestWidget()
{
}

QLabel *ContactRequestWidget::get_title() const noexcept
{
    return _title.get();
}

ListStrWidget *ContactRequestWidget::get_requestsList() const noexcept
{
    return _requestsList.get();
}

QPushButton *ContactRequestWidget::get_acceptButton() const noexcept
{
    return _acceptButton.get();
}

QPushButton *ContactRequestWidget::get_dismissButton() const noexcept
{
    return _dismissButton.get();
}
