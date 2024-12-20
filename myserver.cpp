#include "myserver.h"
#include <QTcpSocket>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>

MyServer::MyServer(QObject *parent) : QTcpServer(parent) {
    initDatabase();
}

bool MyServer::initDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open()) {
        qDebug() << "Database error occurred: " << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)");
    return true;
}

void MyServer::sendResponse(const QByteArray &body, int statusCode) {
    QString statusLine;
    switch (statusCode) {
    case 200:
        statusLine = "HTTP/1.1 200 OK";
        break;
    case 400:
        statusLine = "HTTP/1.1 400 Bad Request";
        break;
    case 405:
        statusLine = "HTTP/1.1 405 Method Not Allowed";
        break;
    default:
        statusLine = "HTTP/1.1 500 Internal Server Error";
        break;
    }

    clientSocket->write(statusLine.toUtf8() + "\r\n");
    clientSocket->write("Content-Type: application/json\r\n");
    clientSocket->write("Connection: close\r\n");
    clientSocket->write("\r\n");
    clientSocket->write(body);
}

void MyServer::startServer() {
    if (!this->listen(QHostAddress::Any, 2323)) {
        qDebug() << "Could not start server!";
    } else {
        qDebug() << "Server started on port 2323.";
        connect(this, &QTcpServer::newConnection, this, &MyServer::newConnection);
    }
}

void MyServer::newConnection() {
    clientSocket = this->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyServer::readData);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);

    qDebug() << "Client connected:" << clientSocket->peerAddress().toString();
}

void MyServer::readData() {
    QByteArray requestData;

    // Read all available data from the socket
    while (clientSocket->canReadLine()) {
        requestData.append(clientSocket->readLine());
    }

    // Check if we have enough data to process
    if (requestData.isEmpty()) {
        qDebug() << "No data received.";
        return;
    }

    QStringList requestLines = QString(requestData).split("\r\n");
    qDebug() << "Splitted string:" << requestLines;

    if (requestLines.size() > 0 && requestLines[0].startsWith("POST")) {
        qDebug() << "Entered check_body:";

        int contentLength = 0;
        QByteArray jsonBody;

        // Process headers and find Content-Length
        for (int i = 1; i < requestLines.size(); ++i) {
            const QString &line = requestLines[i];
            if (line.startsWith("Content-Length:")) {
                contentLength = line.mid(16).toInt();
                qDebug() << "Content length line:" << contentLength;
            } else if (line.isEmpty()) {
                // Empty line indicates the end of headers; JSON body follows
                jsonBody = requestLines.mid(i + 1).join("\r\n").toUtf8();
                break; // Exit loop after processing headers
            }
        }

        // Ensure we have a valid content length and JSON body
        if (contentLength > 0 && jsonBody.size() == contentLength) {
            qDebug() << "Received JSON Body:" << jsonBody;

            // Parse the JSON data
            QJsonDocument doc = QJsonDocument::fromJson(jsonBody);
            if (!doc.isNull() && doc.isObject()) {
                QJsonObject jsonObj = doc.object();
                qDebug() << "JSON object:" << jsonObj;

                // Check for login or registration action
                if (jsonObj.contains("action")) {
                    QString action = jsonObj["action"].toString();
                    if (action == "register") {
                        QString username = jsonObj["username"].toString();
                        QString password = jsonObj["password"].toString();

                        // Call registerUser function and send response based on result
                        if (registerUser(username, password)) {
                            sendResponse("{\"status\": \"REGISTER_SUCCESS\"}", 200);
                        } else {
                            sendResponse("{\"status\": \"REGISTER_FAILURE\"}", 400);
                        }
                    } else if (action == "login") { // Handle login action
                        QString username = jsonObj["username"].toString();
                        QString password = jsonObj["password"].toString();

                        if (validateLogin(username, password)) {
                            sendResponse("{\"status\": \"LOGIN_SUCCESS\"}", 200);
                        } else {
                            qDebug()<<"Bad work, Oleg";
                            sendResponse("{\"status\": \"LOGIN_FAILURE\"}", 400);
                        }
                    } else {
                        sendResponse("{\"status\": \"INVALID_REQUEST\"}", 400);
                    }
                } else {
                    sendResponse("{\"status\": \"INVALID_JSON\"}", 400);
                }
            } else {
                // Invalid JSON format
                sendResponse("{\"status\": \"INVALID_JSON\"}", 400);
            }
        } else {
            sendResponse("{\"status\": \"INVALID_CONTENT_LENGTH\"}", 400);
        }
    } else {
        // Handle other types of requests or errors
        qDebug() << "Unsupported request type.";
        clientSocket->write("HTTP/1.1 405 Method Not Allowed\r\n");
        clientSocket->write("Connection: close\r\n");
        clientSocket->write("\r\n");
    }

    // Close the socket after responding
    clientSocket->disconnectFromHost();
}


bool MyServer::validateLogin(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Query error: " << query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString storedPassword = query.value(0).toString();
        return (storedPassword == password);
    }

    return false;
}


bool MyServer::registerUser(const QString &username, const QString &password) {
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    checkQuery.bindValue(":username", username);

    if (!checkQuery.exec()) {
        qDebug() << "Check query error: " << checkQuery.lastError().text();
        return false;
    }

    checkQuery.next();
    if (checkQuery.value(0).toInt() > 0) {
        return false;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    insertQuery.bindValue(":username", username);
    insertQuery.bindValue(":password", password);

    if (!insertQuery.exec()) {
        qDebug() << "Insert query error: " << insertQuery.lastError().text();
        return false;
    }

    return true;
}
