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

QLabel *ContactRequestWidget::getTitle() const noexcept
{
    return _title.get();
}

ListStrWidget *ContactRequestWidget::getRequestsList() const noexcept
{
    return _requestsList.get();
}

QPushButton *ContactRequestWidget::getAcceptButton() const noexcept
{
    return _acceptButton.get();
}

QPushButton *ContactRequestWidget::getDismissButton() const noexcept
{
    return _dismissButton.get();
}
