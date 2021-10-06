/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** TitledListWithButton
*/

#ifndef TITLEDLISTWITHBUTTON_HPP_
#define TITLEDLISTWITHBUTTON_HPP_

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QBoxLayout>

#include <memory>

#include "ListStrWidget.hpp"

class TitledListWithButton : public QWidget
{
public:
    TitledListWithButton();
    ~TitledListWithButton();

    QLabel *getTitle() const noexcept;
    ListStrWidget *getList() const noexcept;
    QPushButton *getButton() const noexcept;

private:
    std::unique_ptr<QLabel> _title;
    std::unique_ptr<ListStrWidget> _list;
    std::unique_ptr<QPushButton> _button;
};

#endif /* !TITLEDLISTWITHBUTTON_HPP_ */
