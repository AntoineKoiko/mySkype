/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** HomeScreen
*/

#include "HomeScreen.hpp"

HomeScreen::HomeScreen() : QWidget(),
                           _contactsList(std::make_unique<QListWidget>(this)),
                           _newContactList(std::make_unique<QListWidget>(this)),
                           _searchContactField(std::make_unique<QLineEdit>(this)),
                           _mainLayout(std::make_unique<QGridLayout>(this)),
                           _addToCallButton(std::make_unique<QPushButton>(this)),
                           _cancelToCallButton(std::make_unique<QPushButton>(this)),
                           _toCallList(std::make_unique<QListWidget>(this)),
                           _addContactButton(std::make_unique<QPushButton>(this)),
                           _dismissContactButton(std::make_unique<QPushButton>(this)),
                           _acceptContactButton(std::make_unique<QPushButton>(this)),
                           _callButton(std::make_unique<QPushButton>(this)),
                           _contactAddedLabel(std::make_unique<QLabel>(this)),
                           _contactListLabel(std::make_unique<QLabel>(this)),
                           _callListLabel(std::make_unique<QLabel>(this)),
                           _pendingLIstLabel(std::make_unique<QLabel>(this))
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

    _mainLayout->addWidget(_searchContactField.get(), 0, 0, 1, 1);
    _mainLayout->addWidget(_addContactButton.get(), 0, 1, 1, 1);
    _mainLayout->addWidget(_pendingLIstLabel.get(), 1, 3, 1, 1);
    _mainLayout->addWidget(_callListLabel.get(), 4, 3, 1, 1);
    _mainLayout->addWidget(_contactListLabel.get(), 4, 0, 1, 1);

    _mainLayout->addWidget(_contactAddedLabel.get(), 1, 0, 1, 1);
    _mainLayout->addWidget(_newContactList.get(), 2, 3, 2, 1);
    _mainLayout->addWidget(_acceptContactButton.get(), 2, 4, 1, 1);
    _mainLayout->addWidget(_dismissContactButton.get(), 3, 4, 1, 1);
    _mainLayout->addWidget(_contactsList.get(), 5, 0, 1, 2);
    _mainLayout->addWidget(_toCallList.get(), 5, 3, 1, 1);
    _mainLayout->addWidget(_addToCallButton.get(), 6, 0, 1, 1);
    _mainLayout->addWidget(_cancelToCallButton.get(), 6, 3, 1, 1);
    _mainLayout->addWidget(_callButton.get(), 5, 4, 1, 1);

    // _mainLayout->addWidget(_ContactField, 2, 1);

    // _mainLayout->addWidget();

    setLayout(_mainLayout.get());

    connect(_addToCallButton.get(), &QPushButton::clicked,
            this, &HomeScreen::on_addToCallButton_clicked);
    connect(_cancelToCallButton.get(), &QPushButton::clicked,
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
