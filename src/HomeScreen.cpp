/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** HomeScreen
*/

#include "HomeScreen.hpp"

HomeScreen::HomeScreen() : QWidget(),
                           _contactsList(new QListWidget(this)),
                           _searchContactField(new QLineEdit(this)),
                           _mainLayout(new QGridLayout(this)),
                           _addToCallButton(new QPushButton(this)),
                           _cancelToCallButton(new QPushButton(this)),
                           _vLayout(new QVBoxLayout),
                           _toCallList(new QListWidget(this))
{
    _contactsList->setMaximumHeight(800);
    _contactsList->setMaximumWidth(100);
    for (int i = 0; i < 200; i++)
    {
        _contactsList->addItem(QString::number(i));
    }
    _toCallList->setMaximumSize(100, 500);

    _searchContactField->setPlaceholderText("Search New Contact");

    _addToCallButton->setText("Add to Call");

    _cancelToCallButton->setText("Cancel to call");

    _mainLayout->addLayout(_vLayout, 0, 1);
    _mainLayout->addWidget(_searchContactField, 0, 0);
    _mainLayout->addWidget(_contactsList, 1, 0);
    _mainLayout->addWidget(_addToCallButton, 2, 0);

    // _mainLayout->addWidget(_ContactField, 2, 1);
    _mainLayout->addWidget(_toCallList, 1, 1);
    _mainLayout->addWidget(_cancelToCallButton, 2, 1);

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
