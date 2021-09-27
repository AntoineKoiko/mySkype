/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-aurelien.joncour
** File description:
** HomeScreen
*/

#include "HomeScreen.hpp"

HomeScreen::HomeScreen() : QWidget(),
                           _contactWidget(std::make_unique<TitledListWithButton>()),
                           _toCallWidget(std::make_unique<TitledListWithButton>()),
                           _newContactList(std::make_unique<QListWidget>(this)),
                           _searchContactField(std::make_unique<QLineEdit>(this)),
                           _mainLayout(std::make_unique<QGridLayout>(this)),
                           _addContactButton(std::make_unique<QPushButton>(this)),
                           _dismissContactButton(std::make_unique<QPushButton>(this)),
                           _acceptContactButton(std::make_unique<QPushButton>(this)),
                           _callButton(std::make_unique<QPushButton>(this)),
                           _contactAddedLabel(std::make_unique<QLabel>(this)),
                           _pendingLIstLabel(std::make_unique<QLabel>(this))
{
    for (int i = 0; i < 200; i++)
    {
        _contactWidget->get_list()->addItem(QString::number(i));
    }
    _toCallWidget->get_list()->setMaximumSize(100, 500);

    _contactAddedLabel->setText("Conttact Added");

    _searchContactField->setPlaceholderText("Search New Contact");

    _addContactButton->setText("Add to your contact");
    _acceptContactButton->setText("Accept Contact");
    _dismissContactButton->setText("Dismiss Contact");
    _callButton->setText("Call");
    _pendingLIstLabel->setText("Pending LIst");

    _mainLayout->addWidget(_searchContactField.get(), 0, 0, 1, 1);
    _mainLayout->addWidget(_addContactButton.get(), 0, 1, 1, 1);
    _mainLayout->addWidget(_pendingLIstLabel.get(), 1, 3, 1, 1);
    _mainLayout->addWidget(_newContactList.get(), 2, 3, 2, 1);

    _mainLayout->addWidget(_contactAddedLabel.get(), 1, 0, 1, 1);
    _mainLayout->addWidget(_acceptContactButton.get(), 2, 4, 1, 1);
    _mainLayout->addWidget(_dismissContactButton.get(), 3, 4, 1, 1);
    _mainLayout->addWidget(_callButton.get(), 5, 4, 1, 1);

    _mainLayout->addWidget(_contactWidget->get_title(), 4, 0, 1, 1);
    _mainLayout->addWidget(_contactWidget->get_list(), 5, 0, 1, 2);
    _mainLayout->addWidget(_contactWidget->get_button(), 6, 0, 1, 1);

    _mainLayout->addWidget(_toCallWidget->get_title(), 4, 3, 1, 1);
    _mainLayout->addWidget(_toCallWidget->get_list(), 5, 3, 1, 2);
    _mainLayout->addWidget(_toCallWidget->get_button(), 6, 3, 1, 1);

    setLayout(_mainLayout.get());

    connect(_contactWidget->get_button(), &QPushButton::clicked,
            this, &HomeScreen::on_addToCallButton_clicked);
    connect(_toCallWidget->get_button(), &QPushButton::clicked,
            this, &HomeScreen::on_cancelToCallButton_clicked);
}

HomeScreen::~HomeScreen()
{
}

void HomeScreen::on_addToCallButton_clicked()
{
    QList<QListWidgetItem *> selected = _contactWidget->get_list()->selectedItems();

    if (selected.size() != 0)
    {
        for (const auto lt : selected)
        {
            _toCallWidget->get_list()->addItem(lt->text());
        }
    }
}

void HomeScreen::on_cancelToCallButton_clicked()
{
    int row = _toCallWidget->get_list()->currentRow();
    QListWidgetItem *selected = _toCallWidget->get_list()->takeItem(row);

    if (select)
        delete selected;
}

QPushButton *HomeScreen::get_call_button() const noexcept
{
    return _callButton.get();
}
