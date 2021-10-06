/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** HomeScreen
*/

#include "HomeScreen.hpp"
#include "ListStrWidget.hpp"

HomeScreen::HomeScreen(QWidget *parent) : QWidget(parent),
                                          _contactWidget(std::make_unique<TitledListWithButton>()),
                                          _toCallWidget(std::make_unique<TitledListWithButton>()),
                                          _contactRequestWidget(std::make_unique<ContactRequestWidget>()),
                                          _addContactWidget(std::make_unique<AddContactWidget>()),
                                          _callButton(std::make_unique<QPushButton>(this)),
                                          _mainLayout(std::make_unique<QGridLayout>(this))
{
    setUp_widget();
    setup_layout();
    connect_buttons();
    setLayout(_mainLayout.get());
}

void HomeScreen::setUp_widget() noexcept
{
    for (int i = 0; i < 200; i++)
    {
        _contactWidget->getList()->addItem(QString::number(i));
    }

    _callButton->setText("Call");

    _contactWidget->getTitle()->setText("Contact List");
    _contactWidget->getButton()->setText("Add to Call");

    _toCallWidget->getTitle()->setText("People to Call");
    _toCallWidget->getButton()->setText("Cancel to Call");
}

void HomeScreen::connect_buttons() noexcept
{
    connect(_contactWidget->getButton(), &QPushButton::clicked,
            this, &HomeScreen::on_addToCallButton_clicked);
    connect(_toCallWidget->getButton(), &QPushButton::clicked,
            this, &HomeScreen::on_cancelToCallButton_clicked);
}

void HomeScreen::setup_layout() noexcept
{
    _mainLayout->addWidget(_addContactWidget->getSearchField(), 0, 0, 1, 1);
    _mainLayout->addWidget(_addContactWidget->getAddButton(), 0, 1, 1, 1);
    _mainLayout->addWidget(_addContactWidget->getLabel(), 1, 0, 1, 1);

    _mainLayout->addWidget(_contactRequestWidget->getTitle(), 1, 3, 1, 1);
    _mainLayout->addWidget(_contactRequestWidget->getRequestsList(), 2, 3, 2, 1);
    _mainLayout->addWidget(_contactRequestWidget->getAcceptButton(), 2, 4, 1, 1);
    _mainLayout->addWidget(_contactRequestWidget->getDismissButton(), 3, 4, 1, 1);

    _mainLayout->addWidget(_callButton.get(), 5, 4, 1, 1);

    _mainLayout->addWidget(_contactWidget->getTitle(), 4, 0, 1, 1);
    _mainLayout->addWidget(_contactWidget->getList(), 5, 0, 1, 2);
    _mainLayout->addWidget(_contactWidget->getButton(), 6, 0, 1, 2);

    _mainLayout->addWidget(_toCallWidget->getTitle(), 4, 3, 1, 1);
    _mainLayout->addWidget(_toCallWidget->getList(), 5, 3, 1, 1);
    _mainLayout->addWidget(_toCallWidget->getButton(), 6, 3, 1, 1);
}

HomeScreen::~HomeScreen()
{
}

void HomeScreen::on_addToCallButton_clicked()
{
    std::vector<QString> selected = _contactWidget->getList()->getSelectdQStrItems();
    ListStrWidget *toCallList = _toCallWidget->getList();

    if (selected.size() == 0)
        return;
    for (const QString lt : selected)
    {
        if (toCallList->isIn(lt))
            break;
        _toCallWidget->getList()->addItem(lt);
    }
}

void HomeScreen::on_cancelToCallButton_clicked()
{
    _toCallWidget->getList()->deleteSelectedRow();
}

QPushButton *HomeScreen::get_call_button() const noexcept
{
    return _callButton.get();
}

QPushButton *HomeScreen::getAcceptContactButton() const noexcept
{
    return _contactRequestWidget->getAcceptButton();
}

QPushButton *HomeScreen::getDismissContactButton() const noexcept
{
    return _contactRequestWidget->getDismissButton();
}

QPushButton *HomeScreen::getAddContactButton() const noexcept
{
    return _addContactWidget->getAddButton();
}

ListStrWidget *HomeScreen::get_toCallList() const noexcept
{
    return _toCallWidget->getList();
}

AddContactWidget *HomeScreen::getAddContactWidget() const noexcept
{
    return _addContactWidget.get();
}

ListStrWidget *HomeScreen::getContactList() const noexcept
{
    return _contactWidget->getList();
}

ListStrWidget *HomeScreen::getContactRequestList() const noexcept
{
    return _contactRequestWidget->getRequestsList();
}
