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

class TitledListWithButton : public QWidget
{
public:
    TitledListWithButton();
    ~TitledListWithButton();

    QLabel *get_title() const noexcept;
    QListWidget *get_list() const noexcept;
    QPushButton *get_button() const noexcept;
    QVBoxLayout *get_vLayout() const noexcept;

private:
    std::unique_ptr<QLabel> _title;
    std::unique_ptr<QListWidget> _list;
    std::unique_ptr<QPushButton> _button;
    std::unique_ptr<QVBoxLayout> _vLayout;
};

#endif /* !TITLEDLISTWITHBUTTON_HPP_ */
