#include <QApplication>
#include "client.h"
#include "MainWindow.h"
#include "Authentification.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Client client;
    LoginWindow loginWindow;
    MainWindow mainWindow;
    RegistrationWindow registrationWindow;
    registrationWindow.resize(0, 0);

    QObject::connect(&client, &Client::loginSuccess, [&] {mainWindow.show();});
    QObject::connect(&loginWindow, &LoginWindow::registrationChosen, [&] {registrationWindow.show();});
    QObject::connect(&client, &Client::registrationSuccess, [&] {loginWindow.show();});//add msg about registr
    QObject::connect(&registrationWindow, &RegistrationWindow::loginChosen, [&] {loginWindow.show();});

    loginWindow.show();

    return app.exec();
}
