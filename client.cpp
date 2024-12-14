#include "client.h"
#include "MainWindow.h"
#include "Authentification.h"

Client::client() {

    LoginWindow loginWindow; // password: test login: test
    MainWindow mainWindow;
    RegistrationWindow registrationWindow;
    registrationWindow.resize(0, 0);

    QObject::connect(&loginWindow,&LoginWindow::loginSuccessful, this, &Client::loginCheck());
    QObject::connect(&loginWindow, &LoginWindow::registrationChosen, [&] {registrationWindow.show();});
    QObject::connect(&registrationWindow, &RegistrationWindow::loginChosen, [&] {loginWindow.show();});
    QObject::connect(&registrationWindow, &RegistrationWindow::registrationSuccessful, this, &Client::registrationAttempt);

    //maybe do a function for the connection to server
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, client, Client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    //add the code to check if the connection actually established
    socket->connectToHost("127.0.0.1", 2323);

    loginWindow.show();

}

void Client::loginCheck(str login, str password){
    //get 2 strings -> send to server

    //server answers -> emit success/failure
}

void Client::registrationAttempt(str login, str password){
    //get 2 strings -> send to server

    //server answers -> emit success/failure
}

void Client::SendToServer(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << str;
    socket->write(Data);
    ui->lineEdit->clear();
}

void Client::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok) {
        QString str;
        in >> str;
        ui->textBrowser->append(str);
    }
}
