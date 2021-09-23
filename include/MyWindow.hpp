/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** MyWindow
*/

#ifndef MYWINDOW_HPP_
#define MYWINDOW_HPP_

#include <memory>
#include <QApplication>
#include <QPushButton>
#include <vector>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>

class MyWindow : public QMainWindow
{
public:
    MyWindow();
    ~MyWindow();

private slots:
    void handleButton();

private:
    void init_buttons();

private:
    std::unique_ptr<QPushButton> m_bouton = nullptr;
    std::vector<QLabel *> labels{};
    std::vector<QPushButton *> buttons{};

    int offset = 0;
};

#endif /* !MYWINDOW_HPP_ */
