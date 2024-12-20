#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class MyServer : public QTcpServer {
    Q_OBJECT

public:
    explicit MyServer(QObject *parent = nullptr);
    void startServer(); // Method to start the server

private slots:
    void newConnection(); // Slot to handle new connections
    void readData();      // Slot to read data from the client

private:
    QTcpSocket *clientSocket; // Pointer to the client socket

    // Example methods for login and registration
    bool validateLogin(const QString &username, const QString &password);
    bool registerUser(const QString &username, const QString &password);
    bool initDatabase();
    void sendResponse(const QByteArray &body, int statusCode);
};

#endif // MYSERVER_H
