#include "client.h"
#include "MainWindow.h"
#include "Authentification.h"

Client::client() {

    LoginWindow loginWindow; // password: test login: test
    MainWindow mainWindow;
    RegistrationWindow registrationWindow;
    registrationWindow.resize(0, 0);
/*
    QObject::connect(&loginWindow,&LoginWindow::loginSuccessful, this, &Client::loginCheck);
*/
    QObject::connect(this, Client::loginSuccess(), [&] {MainWindow.show()});
    QObject::connect(&loginWindow, &LoginWindow::registrationChosen, [&] {registrationWindow.show();});
    QObject::connect(this, Client::registrationSuccess(), [&] {loginWindow.show();});//add msg about registr
    QObject::connect(&registrationWindow, &RegistrationWindow::loginChosen, [&] {loginWindow.show();});


    //maybe do a function for the connection to server
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, client, Client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    //add the code to check if the connection actually established
    socket->connectToHost("127.0.0.1", 2323);

    loginWindow.show();

}

void Client::loginCheck(QString username, QString password){
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << username << password;
    socket->write(data);
    socket->flush();
    //server answers -> emit success/failure
}

void Client::registrationAttempt(QString username, QString password){
    //send to server 2 strings

    //server answers -> emit success/failure
}

void Client::SendToServer(QString str)//func that sets up the type of info
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
        if(str == "login succesful"){
            emit loginSuccess();
        }
        else if(str == "login error"){
            //emit sadness
        }
        else if(str == "registration succesful"){
            emit registrationSuccess();
        }
        else if(str == "registration error"){
            //emit sadness 2
        }//other cases...
    }
}
