/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** ListStrWidget
*/

#include "ListStrWidget.hpp"

ListStrWidget::ListStrWidget(QWidget *parent) : QListWidget(parent)
{
}

ListStrWidget::~ListStrWidget()
{
}

//////////////////////

QString ListStrWidget::itemQStr(const std::size_t i) const
{
    return item(i)->text();
}

std::vector<QString> ListStrWidget::getQStrItems() const noexcept
{
    std::vector<QString> strIt;

    for (int i = 0; i < this->count(); i++)
        strIt.push_back(this->itemQStr(i));
    return strIt;
}

std::vector<QString> ListStrWidget::getSelectdQStrItems() const noexcept
{
    QList<QListWidgetItem *> selected = this->selectedItems();
    std::vector<QString> strList;

    for (const auto lt : selected)
        strList.push_back(lt->text());
    return strList;
}

bool ListStrWidget::isIn(const std::string &str) const noexcept
{
    QString qstr = QString::fromStdString(str);

    for (int i = 0; i < this->count(); i++)
    {
        if (this->itemQStr(i) == qstr)
            return true;
    }
    return false;
}

bool ListStrWidget::isIn(const QString &str) const noexcept
{
    for (int i = 0; i < this->count(); i++)
    {
        if (this->itemQStr(i) == str)
            return true;
    }
    return false;
}

void ListStrWidget::deleteSelectedRow() noexcept
{
    int row = this->currentRow();
    QListWidgetItem *selected = this->takeItem(row);

    if (selected)
        delete selected;
}
