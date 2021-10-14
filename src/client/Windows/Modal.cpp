/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Modal
*/

#include "Modal.hpp"

bool Modal::YesNo(QWidget *parent, const std::string &title, const std::string &msg)
{
    QString qTitle = QString::fromStdString(title);
    QString qMsg = QString::fromStdString(msg);

    return Modal::YesNo(parent, qTitle, qMsg);
}

bool Modal::YesNo(QWidget *parent, const QString &title, const QString &msg)
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(parent, title, msg,
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
        return true;
    return false;
}
