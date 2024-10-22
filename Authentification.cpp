#include "Authentification.h"

#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    QFormLayout *formLayout = new QFormLayout(this);

    loginLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);

    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *loginButton = new QPushButton("Войти", this);
    QPushButton *registrationButton = new QPushButton("Перейти в режим: Регистрация", this);

    formLayout->addRow("&Логин:", loginLineEdit);
    formLayout->addRow("&Пароль:", passwordLineEdit);
    formLayout->addWidget(loginButton);
    formLayout->addWidget(registrationButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::checkLoginAndPassword);
    connect(registrationButton, &QPushButton::clicked, this, &LoginWindow::chooseRegistration);
}

void LoginWindow::chooseRegistration() {
    emit registrationChosen();
    close();
}

void LoginWindow::checkLoginAndPassword() {
    QString username = loginLineEdit->text();
    QString password = passwordLineEdit->text();

    // Replace these with actual data validation
    const QString correctUsername = "test";
    const QString correctPassword = "test";

    if (username == correctUsername && password == correctPassword) {
        emit loginSuccessful();
        close();
    } else {
        QMessageBox::warning(this, "LOGIN ERROR!", "Wrong login or password!");
    }
}

RegistrationWindow::RegistrationWindow(QWidget *parent) : QWidget(parent) {
    // Create layout and widgets
    QFormLayout *formLayout = new QFormLayout(this);

    loginLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);

    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *registrationButton = new QPushButton("Зарегистрироваться", this);
    QPushButton *chooseLoginButton = new QPushButton("Перейти в режим: вход", this);

    formLayout->addRow("&Логин:", loginLineEdit);
    formLayout->addRow("&Пароль:", passwordLineEdit);

    formLayout->addWidget(registrationButton);
    formLayout->addWidget(chooseLoginButton);

    connect(registrationButton, &QPushButton::clicked, this, &RegistrationWindow::registration);
    connect(chooseLoginButton, &QPushButton::clicked, this, &RegistrationWindow::chooseLogin);
}

bool RegistrationWindow::checkLogin(const QString &username) {
    // Implement actual logic forlogin correctness
    return true;
}

bool RegistrationWindow::checkPassword(const QString &password) {
    // Implement actual logic for password correctness
    return true;
}

void RegistrationWindow::chooseLogin() {
    emit loginChosen();
}

void RegistrationWindow::registration() {
    QString username = loginLineEdit->text();
    QString password = passwordLineEdit->text();

    if (checkLogin(username) && checkPassword(password)) {
        emit registrationSuccessful();
        close();
    }
}
