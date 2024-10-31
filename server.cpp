#include "server.h"

Server::Server() {
    if(this->listen(QHostAddress::Any, 2323)) {
        qDebug() << "start";
    }
    else {
        qDebug() << "error";
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::slotClientDisconnected);

    Sockets.push_back(socket);

    qDebug() << "client connected" << socketDescriptor;
}

void Server::slotReadyRead() {
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok) {
        QString str;
        in >> str;
        qDebug() << str;
        SendToClient(str);
    }
}

void Server::slotClientDisconnected()
{
    socket = (QTcpSocket*)sender();
    Sockets.erase(std::remove(Sockets.begin(), Sockets.end(), socket), Sockets.end());
    socket->deleteLater();
}

void Server::SendToClient(QString str) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << str;
    for (int i = 0; i < Sockets.size(); i++) {
        Sockets[i]->write(Data);
    }
}






