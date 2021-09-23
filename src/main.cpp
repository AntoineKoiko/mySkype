#include <QApplication>
#include <QPushButton>

#include <QWidget>
#include "MyWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyWindow window;

    window.showMaximized();
    return app.exec();
}