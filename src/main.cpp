#include <QApplication>
#include <QPushButton>

#include <QWidget>
#include "MyWindow.hpp"
#include "LoginScreen.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    LoginScreen log;
    log.show();
    // MyWindow window;

    // window.showMaximized();
    return app.exec();
}