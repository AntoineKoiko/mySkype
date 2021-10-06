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
                                               _button(std::make_unique<QPushButton>(this)),
                                               _vLayout(std::make_unique<QVBoxLayout>())
{
    _title->setText("unknown");
    _button->setText("unknown");

    _vLayout->addWidget(_title.get());
    _vLayout->addWidget(_list.get(), Qt::AbsoluteSize);
    _vLayout->addWidget(_button.get());

    setLayout(_vLayout.get());
}

TitledListWithButton::~TitledListWithButton()
{
}

QLabel *TitledListWithButton::get_title() const noexcept
{
    return _title.get();
}

ListStrWidget *TitledListWithButton::get_list() const noexcept
{
    return _list.get();
}

QPushButton *TitledListWithButton::get_button() const noexcept
{
    return _button.get();
}

QVBoxLayout *TitledListWithButton::get_vLayout() const noexcept
{
    return _vLayout.get();
}
