#include "Authentification.h"
#include <QFontDialog>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {

    QFont fonti("Cascadia Mono SemiBold", 12);
    this->setFont(fonti);
    this->setFixedSize(400, 300);

    QFormLayout *formLayout = new QFormLayout(this);
    loginLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);

    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *loginButton = new QPushButton("Login", this);
    QPushButton *registrationButton = new QPushButton("Switch to registration", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(registrationButton);

    formLayout->addRow("&Login:", loginLineEdit);
    formLayout->addRow("&Password:", passwordLineEdit);
    formLayout->addRow(buttonLayout);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::checkLoginAndPassword);
    connect(registrationButton, &QPushButton::clicked, this, &LoginWindow::chooseRegistration);
    formLayout->setSpacing(75);

    QPushButton button("Select Font", this);
    QObject::connect(&button, &QPushButton::clicked, [&]() {
        bool ok;
        QFont selectedFont = QFontDialog::getFont(&ok);
        if (ok) {
            this->setFont(selectedFont);

        }
    });
    formLayout->addWidget(&button);
}

void LoginWindow::chooseRegistration() {
    emit registrationChosen();
    close();
}

void LoginWindow::checkLoginAndPassword() {
    QString username = loginLineEdit->text();
    QString password = passwordLineEdit->text();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QJsonObject json;
    json["action"] = "login";
    json["username"] = username;
    json["password"] = password;

    QJsonDocument doc(json);

    // Send POST request to the server for login
    QNetworkRequest request(QUrl("http://localhost:2323/login")); // Adjust URL as needed
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    manager->post(request, doc.toJson());

    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
        QString response = reply->readAll();
        qDebug() << "Login Response:" << response;
        if (reply->error() == QNetworkReply::NoError) {

            QJsonDocument responseDoc = QJsonDocument::fromJson(response.toUtf8());
            if (!responseDoc.isNull() && responseDoc.isObject()) {
                QJsonObject responseObj = responseDoc.object();
                QString status = responseObj["status"].toString();

                if (status == "LOGIN_SUCCESS") {
                    emit loginSuccessful();
                    close();
                } else if (status == "LOGIN_FAILURE") {
                    QMessageBox::warning(this, "LOGIN ERROR!", "Incorrect login or password!");
                } else {
                    QMessageBox::warning(this, "LOGIN ERROR!", "An unknown error occurred.");
                }
            } else {
                QMessageBox::warning(this, "LOGIN ERROR!", "Invalid response format from server.");
            }
        } else {
            QMessageBox::warning(this, "LOGIN ERROR!", reply->errorString());
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}



RegistrationWindow::RegistrationWindow(QWidget *parent) : QWidget(parent) {
    QFont fonti("Cascadia Mono SemiBold", 12);
    this->setFont(fonti);
    this->setFixedSize(400, 300);
    QFormLayout *formLayout = new QFormLayout(this);

    this->setFixedSize(400, 300);

    loginLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);

    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *registrationButton = new QPushButton("Register", this);
    QPushButton *chooseLoginButton = new QPushButton("Switch to login mode", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(registrationButton);
    buttonLayout->addWidget(chooseLoginButton);

    formLayout->addRow("&Login:", loginLineEdit);
    formLayout->addRow("&Password:", passwordLineEdit);
    formLayout->addRow(buttonLayout);

    formLayout->setSpacing(75);

    connect(registrationButton, &QPushButton::clicked, this, &RegistrationWindow::registration);
    connect(chooseLoginButton, &QPushButton::clicked, this, &RegistrationWindow::chooseLogin);
}

bool RegistrationWindow::checkLogin(const QString &username) {
     return !username.isEmpty();
}

bool RegistrationWindow::checkPassword(const QString &password) {
    return password.length() >= 6;

}

void RegistrationWindow::chooseLogin() {
    emit loginChosen();
    close();
}

void RegistrationWindow::registration() {
    QString username = loginLineEdit->text();
    QString password = passwordLineEdit->text();

    if (!checkLogin(username)) {
        QMessageBox::warning(this, "REGISTRATION ERROR!", "Username cannot be empty!");
        return;
    }

    if (!checkPassword(password)) {
        QMessageBox::warning(this, "REGISTRATION ERROR!", "Password must be at least 6 characters long!");
        return;
    }

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QJsonObject json;
    json["action"] = "register";
    json["username"] = username;
    json["password"] = password;

    QJsonDocument doc(json);

     qDebug() << "Sending JSON Data:" << doc.toJson();

    // Send POST request to the server for registration
    QNetworkRequest request(QUrl("http://localhost:2323/register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    manager->post(request,doc.toJson());

    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
        QString response = reply->readAll();
        qDebug() << "Registration Response:" << response;
        if (reply->error() == QNetworkReply::NoError) {

            // Parse the JSON response to check for status
            QJsonDocument responseDoc = QJsonDocument::fromJson(response.toUtf8());
            if (!responseDoc.isNull() && responseDoc.isObject()) {
                QJsonObject responseObj = responseDoc.object();
                QString status = responseObj["status"].toString();

                if (status == "REGISTER_SUCCESS") {
                    emit registrationSuccessful();
                    close();
                } else if (status == "REGISTER_FAILURE") {
                    QMessageBox::warning(this, "REGISTRATION ERROR!", "Username already exists!");
                } else {
                    QMessageBox::warning(this, "REGISTRATION ERROR!", "An unknown error occurred.");
                }
            } else {
                QMessageBox::warning(this, "REGISTRATION ERROR!", "Invalid response format from server.");
            }
        } else {
            // Handle network errors
            QMessageBox::warning(this, "REGISTRATION ERROR!", reply->errorString());
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}
