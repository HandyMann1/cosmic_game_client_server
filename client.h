#pragma once
#include <QTcpSocket>

class Client
{
private:
    void SendToServer(QString str);
public:
    Client();
public slots:
    void slotReadyRead();
    void loginCheck(str login, str password);
    void registrationAttempt(str login, str password);
};
