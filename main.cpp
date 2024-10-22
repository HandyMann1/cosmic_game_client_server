#include <QApplication>
#include "MainWindow.h"
#include"Authentification.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LoginWindow loginWindow; // password: test login: test
    MainWindow mainWindow;
    RegistrationWindow registrationWindow;

    QObject::connect(&loginWindow,&LoginWindow::loginSuccessful, [&] {mainWindow.show();});
    QObject::connect(&loginWindow, &LoginWindow::registrationChosen, [&] {registrationWindow.show();});
    QObject::connect(&registrationWindow, &RegistrationWindow::loginChosen, [&] {loginWindow.show();});
    loginWindow.show();

    return app.exec();
}