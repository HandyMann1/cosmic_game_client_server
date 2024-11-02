#include "Authentification.h"

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    QFormLayout *formLayout = new QFormLayout(this);
    loginLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);


    this->setFixedSize(400, 300);

    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *loginButton = new QPushButton("Войти", this);
    QPushButton *registrationButton = new QPushButton("Перейти в режим: Регистрация", this);


    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(registrationButton);

    formLayout->addRow("&Логин:", loginLineEdit);
    formLayout->addRow("&Пароль:", passwordLineEdit);
    formLayout->addRow(buttonLayout);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::checkLoginAndPassword);
    connect(registrationButton, &QPushButton::clicked, this, &LoginWindow::chooseRegistration);
    formLayout->setSpacing(75);
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
    QFormLayout *formLayout = new QFormLayout(this);

    this->setFixedSize(400, 300);

    loginLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);

    passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *registrationButton = new QPushButton("Зарегистрироваться", this);
    QPushButton *chooseLoginButton = new QPushButton("Перейти в режим: вход", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(registrationButton);
    buttonLayout->addWidget(chooseLoginButton);

    formLayout->addRow("&Логин:", loginLineEdit);
    formLayout->addRow("&Пароль:", passwordLineEdit);
    formLayout->addRow(buttonLayout);

    formLayout->setSpacing(75);

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
    close();
}

void RegistrationWindow::registration() {
    QString username = loginLineEdit->text();
    QString password = passwordLineEdit->text();

    if (checkLogin(username) && checkPassword(password)) {
        emit registrationSuccessful();
        close();
    }
}
