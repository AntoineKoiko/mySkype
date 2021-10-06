/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** CallScreen
*/

#ifndef CALLSCREEN_HPP_
#define CALLSCREEN_HPP_

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>

#include <memory>
#include <vector>
#include <string>

class CallScreen : public QWidget
{
public:
    explicit CallScreen(QWidget *parent);
    ~CallScreen();

    void startCall(const std::vector<QString> &contacts);
    void stopCall();

    QPushButton *getHangUpButton() const noexcept;

private:
    std::unique_ptr<QLabel> _inCallLabel;
    std::vector<std::unique_ptr<QLabel>> _inCallList;
    std::unique_ptr<QPushButton> _hangUpButton;
    std::unique_ptr<QLabel> _padTop;
    std::unique_ptr<QLabel> _padBot;

    std::unique_ptr<QVBoxLayout> _layout;
};

#endif /* !CALLSCREEN_HPP_ */
