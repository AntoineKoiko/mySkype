/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** MyWindow
*/

#include "MyWindow.hpp"
#include <iostream>

MyWindow::MyWindow()
{
    // setFixedSize(300, 150);

    // Construction du bouton
    init_buttons();
}

void MyWindow::init_buttons()
{
    m_bouton = std::make_unique<QPushButton>("Pimp mon bouton !", this);

    m_bouton->setFont(QFont("Comic Sans MS", 14));
    m_bouton->setCursor(Qt::PointingHandCursor);
    m_bouton->setIcon(QIcon("smile.png"));
    m_bouton->move(200, 50);

    // connect(m_bouton.get(), &QPushButton::released, this, SLOT(handleButton()));
    connect(m_bouton.get(), &QPushButton::released, this, &MyWindow::handleButton);
}

MyWindow::~MyWindow()
{
}

void MyWindow::handleButton()
{
    QPushButton *btn = new QPushButton("John Bob", this);

    btn->setFont(QFont("Comic Sans MS", 14));
    btn->setCursor(Qt::PointingHandCursor);
    btn->setIcon(QIcon("smile.png"));
    btn->move(10, this->offset);
    this->offset += 50;
    btn->setFlat(true);
    btn->show();
    buttons.push_back(btn);
    // QLabel *label = new QLabel(this);
    // label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    // label->setText("first line\nsecond line");
    // label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    // labels.push_back(label);
    // label->move(10, this->offset);
    // this->offset += 10;
    // label->show();
    // change the text
    // outon->setText("Example");
    // // resize button
    // m_bouton->resize(100, 100);m_b
    std::cout << "test" << std::endl;
};
