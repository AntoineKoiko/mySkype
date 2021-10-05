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
        _contactWidget->get_list()->addItem(QString::number(i));
    }

    _callButton->setText("Call");

    _contactWidget->get_title()->setText("Contact List");
    _contactWidget->get_button()->setText("Add to Call");

    _toCallWidget->get_title()->setText("People to Call");
    _toCallWidget->get_button()->setText("Cancel to Call");
}

void HomeScreen::connect_buttons() noexcept
{
    connect(_contactWidget->get_button(), &QPushButton::clicked,
            this, &HomeScreen::on_addToCallButton_clicked);
    connect(_toCallWidget->get_button(), &QPushButton::clicked,
            this, &HomeScreen::on_cancelToCallButton_clicked);
}

void HomeScreen::setup_layout() noexcept
{
    _mainLayout->addWidget(_addContactWidget->get_searchField(), 0, 0, 1, 1);
    _mainLayout->addWidget(_addContactWidget->get_addButton(), 0, 1, 1, 1);
    _mainLayout->addWidget(_addContactWidget->get_label(), 1, 0, 1, 1);

    _mainLayout->addWidget(_contactRequestWidget->get_title(), 1, 3, 1, 1);
    _mainLayout->addWidget(_contactRequestWidget->get_requestsList(), 2, 3, 2, 1);
    _mainLayout->addWidget(_contactRequestWidget->get_acceptButton(), 2, 4, 1, 1);
    _mainLayout->addWidget(_contactRequestWidget->get_dismissButton(), 3, 4, 1, 1);

    _mainLayout->addWidget(_callButton.get(), 5, 4, 1, 1);

    _mainLayout->addWidget(_contactWidget->get_title(), 4, 0, 1, 1);
    _mainLayout->addWidget(_contactWidget->get_list(), 5, 0, 1, 2);
    _mainLayout->addWidget(_contactWidget->get_button(), 6, 0, 1, 2);

    _mainLayout->addWidget(_toCallWidget->get_title(), 4, 3, 1, 1);
    _mainLayout->addWidget(_toCallWidget->get_list(), 5, 3, 1, 1);
    _mainLayout->addWidget(_toCallWidget->get_button(), 6, 3, 1, 1);
}

HomeScreen::~HomeScreen()
{
}

void HomeScreen::on_addToCallButton_clicked()
{
    std::vector<QString> selected = _contactWidget->get_list()->getSelectdQStrItems();
    ListStrWidget *toCallList = _toCallWidget->get_list();

    if (selected.size() == 0)
        return;
    for (const QString lt : selected)
    {
        if (toCallList->isIn(lt))
            break;
        _toCallWidget->get_list()->addItem(lt);
    }
}

void HomeScreen::on_cancelToCallButton_clicked()
{
    _toCallWidget->get_list()->deleteSelectedRow();
}

QPushButton *HomeScreen::get_call_button() const noexcept
{
    return _callButton.get();
}

QPushButton *HomeScreen::getAcceptContactButton() const noexcept
{
    return _contactRequestWidget->get_acceptButton();
}

QPushButton *HomeScreen::getDismissContactButton() const noexcept
{
    return _contactRequestWidget->get_dismissButton();
}

QPushButton *HomeScreen::getAddContactButton() const noexcept
{
    return _addContactWidget->get_addButton();
}

ListStrWidget *HomeScreen::get_toCallList() const noexcept
{
    return _toCallWidget->get_list();
}

AddContactWidget *HomeScreen::getAddContactWidget() const noexcept
{
    return _addContactWidget.get();
}

ListStrWidget *HomeScreen::getContactList() const noexcept
{
    return _contactWidget->get_list();
}

ListStrWidget *HomeScreen::getContactRequestList() const noexcept
{
    return _contactRequestWidget->get_requestsList();
}
