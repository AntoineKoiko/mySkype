/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** Modal
*/

#ifndef MODAL_HPP_
#define MODAL_HPP_

#include <QMessageBox>
#include <string>

class Modal
{
public:
    static bool YesNo(QWidget *parent, const std::string &title, const std::string &msg);
    static bool YesNo(QWidget *parent, const QString &title, const QString &msg);
};

#endif /* !MODAL_HPP_ */
