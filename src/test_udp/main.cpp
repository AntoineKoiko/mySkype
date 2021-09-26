//main.cpp

#include <QCoreApplication>
#include "Udp.hpp"
#include "App.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc != 3) {
        std::cout << "./babel_server <port1> <port2>" << std::endl;
        return 1;
    }
    App app(atoi(argv[1]), atoi(argv[2]));
    app.run();
    QObject::connect(&app, SIGNAL(quit()), &a, SLOT(quit()));

    std::cout << "Launch Minimal App" << std::endl;
    return a.exec();
}
