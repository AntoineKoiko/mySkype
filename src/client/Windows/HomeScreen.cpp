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
                                          _usernameLabel(std::make_unique<QLabel>(this)),
                                          _inputComboBox(std::make_unique<QComboBox>(this)),
                                          _mainLayout(std::make_unique<QGridLayout>(this))
{
    this->setStyleSheet("background-color:#8789E8;color:#0E312C;");

    setUpWidget();
    setupLayout();
    connectButtons();
    setLayout(_mainLayout.get());
}

void HomeScreen::setUpWidget() noexcept
{
    _usernameLabel->setAlignment(Qt::AlignCenter);
    _usernameLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    _usernameLabel->setFont(QFont("Arial", 16, QFont::Bold));

    _inputComboBox->addItem("micro 1");
    _inputComboBox->addItem("micro 2");
    _inputComboBox->addItem("micro 3");
    _inputComboBox->addItem("micro 4");

    _callButton->setText("Call");

    _contactWidget->getTitle()->setText("Contact List");
    _contactWidget->getButton()->setText("Add to Call");

    _toCallWidget->getTitle()->setText("People to Call");
    _toCallWidget->getButton()->setText("Cancel to Call");
}

void HomeScreen::connectButtons() noexcept
{
    connect(_contactWidget->getButton(), &QPushButton::clicked,
            this, &HomeScreen::onAddToCallButtonClicked);
    connect(_toCallWidget->getButton(), &QPushButton::clicked,
            this, &HomeScreen::onCancelToCallButtonClicked);
}

void HomeScreen::setupLayout() noexcept
{
    _mainLayout->addWidget(_addContactWidget->getSearchField(), 0, 0, 1, 1);
    _mainLayout->addWidget(_addContactWidget->getAddButton(), 0, 1, 1, 1);
    _mainLayout->addWidget(_addContactWidget->getLabel(), 1, 0, 1, 1);
    _mainLayout->addWidget(_inputComboBox.get(), 2, 0, 1, 1);

    _mainLayout->addWidget(_usernameLabel.get(), 0, 3, 1, 2);

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

QString HomeScreen::getSelectedDevice() const noexcept
{
    return _inputComboBox->itemData(_inputComboBox->currentIndex()).toString();
}

// SLOTS

void HomeScreen::onAddToCallButtonClicked()
{
    std::vector<QString> selected = _contactWidget->getList()->getSelectdQStrItems();
    ListStrWidget *toCallList = _toCallWidget->getList();

    if (selected.size() == 0)
        return;
    for (const QString &lt : selected)
    {
        if (toCallList->isIn(lt))
            break;
        _toCallWidget->getList()->addItem(lt);
    }
}

void HomeScreen::onCancelToCallButtonClicked()
{
    _toCallWidget->getList()->deleteSelectedRow();
}

QPushButton *HomeScreen::getCallButton() const noexcept
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

ListStrWidget *HomeScreen::getToCallList() const noexcept
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

void HomeScreen::setUsername(const std::string &username) const noexcept
{
    std::string buf = std::string("Hello ") + username + std::string(" !");
    _usernameLabel->setText(QString::fromStdString(buf));
}
