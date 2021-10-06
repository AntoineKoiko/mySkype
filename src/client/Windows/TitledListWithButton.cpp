/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** TitledListWithButton
*/

#include "TitledListWithButton.hpp"

TitledListWithButton::TitledListWithButton() : QWidget(),
                                               _title(std::make_unique<QLabel>(this)),
                                               _list(std::make_unique<ListStrWidget>(this)),
                                               _button(std::make_unique<QPushButton>(this))
{
    _title->setText("unknown");
    _button->setText("unknown");
}

TitledListWithButton::~TitledListWithButton()
{
}

QLabel *TitledListWithButton::getTitle() const noexcept
{
    return _title.get();
}

ListStrWidget *TitledListWithButton::getList() const noexcept
{
    return _list.get();
}

QPushButton *TitledListWithButton::getButton() const noexcept
{
    return _button.get();
}
