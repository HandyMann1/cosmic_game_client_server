#include "Authentification.h"
#include <QFontDialog>

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

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::checkLoginAndPassword);//replacing this into client.cpp
    connect(registrationButton, &QPushButton::clicked, this, &LoginWindow::chooseRegistration);//and this
    formLayout->setSpacing(75);

    QPushButton button("Select Font", this);
    QObject::connect(&button, &QPushButton::clicked, [&]() {
        bool ok;
        QFont selectedFont = QFontDialog::getFont(&ok);
        if (ok) {
            // Apply the selected font globally
            this->setFont(selectedFont);
            // Or apply it to specific widgets
            // button.setFont(selectedFont);
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

    emit tryLogin(username, password);


    // Replace these with actual data validation
    //     14.12: this should be in client.cpp, not here
    const QString correctUsername = "test";
    const QString correctPassword = "test";

    if (username == correctUsername && password == correctPassword) {
        //emit main screen idk
        return 0;
    }
/*    if (username == correctUsername && password == correctPassword) {
        emit tryLogin(username, password);//it was auto-logging in
        close();
    } else {
        QMessageBox::warning(this, "LOGIN ERROR!", "Wrong login or password!");
    }*/ //old logic
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
        emit tryRegistration(username, password);
        close();
    }
}
