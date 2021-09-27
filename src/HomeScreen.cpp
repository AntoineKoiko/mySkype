/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** HomeScreen
*/

#include "HomeScreen.hpp"

HomeScreen::HomeScreen() : QWidget(),
                           _contactsList(new QListWidget(this)),
                           _newContactList(new QListWidget(this)),
                           _searchContactField(new QLineEdit(this)),
                           _mainLayout(new QGridLayout(this)),
                           _addToCallButton(new QPushButton(this)),
                           _cancelToCallButton(new QPushButton(this)),
                           _toCallList(new QListWidget(this)),
                           _addContactButton(new QPushButton(this)),
                           _dismissContactButton(new QPushButton(this)),
                           _acceptContactButton(new QPushButton(this)),
                           _callButton(new QPushButton(this)),
                           _contactAddedLabel(new QLabel(this)),
                           _contactListLabel(new QLabel(this)),
                           _callListLabel(new QLabel(this)),
                           _pendingLIstLabel(new QLabel(this))
{
    for (int i = 0; i < 200; i++)
    {
        _contactsList->addItem(QString::number(i));
    }
    _toCallList->setMaximumSize(100, 500);

    _contactAddedLabel->setText("Conttact Added");

    _searchContactField->setPlaceholderText("Search New Contact");

    _addToCallButton->setText("Add to Call");
    _cancelToCallButton->setText("Cancel to call");
    _addContactButton->setText("Add to your contact");
    _acceptContactButton->setText("Accept Contact");
    _dismissContactButton->setText("Dismiss Contact");
    _callButton->setText("Call");
    _contactListLabel->setText("Contact List");
    _callListLabel->setText("Call list");
    _pendingLIstLabel->setText("Pending LIst");

    _mainLayout->addWidget(_searchContactField, 0, 0, 1, 1);
    _mainLayout->addWidget(_addContactButton, 0, 1, 1, 1);
    _mainLayout->addWidget(_pendingLIstLabel, 1, 3, 1, 1);
    _mainLayout->addWidget(_callListLabel, 4, 3, 1, 1);
    _mainLayout->addWidget(_contactListLabel, 4, 0, 1, 1);

    _mainLayout->addWidget(_contactAddedLabel, 1, 0, 1, 1);
    _mainLayout->addWidget(_newContactList, 2, 3, 2, 1);
    _mainLayout->addWidget(_acceptContactButton, 2, 4, 1, 1);
    _mainLayout->addWidget(_dismissContactButton, 3, 4, 1, 1);
    _mainLayout->addWidget(_contactsList, 5, 0, 1, 2);
    _mainLayout->addWidget(_toCallList, 5, 3, 1, 1);
    _mainLayout->addWidget(_addToCallButton, 6, 0, 1, 1);
    _mainLayout->addWidget(_cancelToCallButton, 6, 3, 1, 1);
    _mainLayout->addWidget(_callButton, 5, 4, 1, 1);

    // _mainLayout->addWidget(_ContactField, 2, 1);

    // _mainLayout->addWidget();

    setLayout(_mainLayout);

    connect(_addToCallButton, &QPushButton::clicked,
            this, &HomeScreen::on_addToCallButton_clicked);
    connect(_cancelToCallButton, &QPushButton::clicked,
            this, &HomeScreen::on_cancelToCallButton_clicked);
}

HomeScreen::~HomeScreen()
{
}

void HomeScreen::on_addToCallButton_clicked()
{
    QList<QListWidgetItem *> selected = _contactsList->selectedItems();

    if (selected.size() != 0)
    {
        for (const auto lt : selected)
        {
            _toCallList->addItem(lt->text());
        }
    }
}

void HomeScreen::on_cancelToCallButton_clicked()
{
    int row = _toCallList->currentRow();
    QListWidgetItem *selected = _toCallList->takeItem(row);

    if (select)
        delete selected;
}
