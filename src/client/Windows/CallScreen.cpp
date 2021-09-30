/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** CallScreen
*/

#include "CallScreen.hpp"

CallScreen::CallScreen(QWidget *parent) : QWidget(parent),
                                          _inCallLabel(std::make_unique<QLabel>()),
                                          _hangUpButton(std::make_unique<QPushButton>()),
                                          _layout(std::make_unique<QVBoxLayout>())
{
    _inCallLabel->setText("In Call With:");
    setLayout(_layout.get());
}

CallScreen::~CallScreen()
{
}

void CallScreen::start_call(const std::vector<QString> &contacts)
{
    _layout->addWidget(_inCallLabel.get());

    for (const QString &lt : contacts)
    {
        std::unique_ptr<QLabel> buf = std::make_unique<QLabel>();
        buf->setText(lt);
        _layout->addWidget(buf.get());
        _inCallList.push_back(std::move(buf));
    }
    _layout->addWidget(_hangUpButton.get());
}

void CallScreen::stop_call()
{
    _inCallList.clear();
}

QPushButton *CallScreen::get_hangUp_button() const noexcept
{
    return _hangUpButton.get();
}
