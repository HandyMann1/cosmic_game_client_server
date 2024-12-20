#pragma once
#include <QTcpSocket>
#include <QWidget>

class Client : public QWidget
{
    Q_OBJECT
private:
    void SendToServer(QString str);
    QTcpSocket *socket;
    QByteArray Data;
public:
    Client();
public slots:
    void slotReadyRead();
    void loginCheck(QString username, QString password);
    void registrationAttempt(QString username, QString password);
signals:
    void loginSuccess();
    void registrationSuccess();
};
