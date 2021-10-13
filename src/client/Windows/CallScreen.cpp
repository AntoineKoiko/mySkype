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
                                          _padTop(std::make_unique<QLabel>()),
                                          _padBot(std::make_unique<QLabel>()),
                                          _layout(std::make_unique<QVBoxLayout>())

{
    _inCallLabel->setText("In Call With:");
    _inCallLabel->setAlignment(Qt::AlignCenter);
    _hangUpButton->setText("Hang Up");

    setLayout(_layout.get());
}

CallScreen::~CallScreen()
{
}

void CallScreen::startCall(const std::vector<QString> &contacts)
{
    _layout->addWidget(_inCallLabel.get());
    _layout->addWidget(_padTop.get(), 1);

    for (const QString &lt : contacts)
    {
        std::unique_ptr<QLabel> buf = std::make_unique<QLabel>();
        buf->setText(lt);
        buf->setAlignment(Qt::AlignCenter);
        _layout->addWidget(buf.get());
        _inCallList.push_back(std::move(buf));
    }
    _layout->addWidget(_padBot.get(), 1);
    _layout->addWidget(_hangUpButton.get());
}

void CallScreen::stopCall()
{
    _inCallList.clear();
}

QPushButton *CallScreen::getHangUpButton() const noexcept
{
    return _hangUpButton.get();
}
