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
    void loginCheck(str username, str password);
    void registrationAttempt(str username, str password);
signals:
    void loginSuccess();
    void registrationSuccess();
};
