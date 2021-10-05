/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** ListStrWidget
*/

#ifndef LISTSTRWIDGET_HPP_
#define LISTSTRWIDGET_HPP_

#include <QListWidget>

#include <string>
#include <vector>

class ListStrWidget : public QListWidget
{
public:
    explicit ListStrWidget(QWidget *parent);
    ~ListStrWidget();

    QString itemQStr(const std::size_t i) const;
    std::vector<QString> getQStrItems() const noexcept;

    bool isIn(const std::string &str) const noexcept;
    bool isIn(const QString &str) const noexcept;

    void deleteSelectedRow() noexcept;
};

#endif /* !LISTSTRWIDGET_HPP_ */
