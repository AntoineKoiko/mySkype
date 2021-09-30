/*
** EPITECH PROJECT, 2021
** babel
** File description:
** main
*/

#include "AudioDecoder.hpp"
#include "AudioEncoder.hpp"
#include "AudioInput.hpp"
#include "AudioOutput.hpp"
#include <QApplication>
#include "MyWindow.hpp"

using namespace Babel::Client::Audio;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // LoginScreen log;
    // log.show();
    // HomeScreen home;
    // home.show();
    MyWindow window;

    window.show();
    return app.exec();
}