#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include <QStyle>


//qstyle


class LoginWindow : public QWidget {
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);

public slots:
    void checkLoginAndPassword();
    void chooseRegistration();

signals:
    void loginSuccessful();
    void registrationChosen();

private:
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
};

class RegistrationWindow : public QWidget {
    Q_OBJECT
public:
    explicit RegistrationWindow(QWidget *parent = nullptr);

public slots:
    void registration();
    void chooseLogin();

signals:
    void registrationSuccessful();
    void loginChosen();

private:
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    bool checkLogin(const QString &username);
    bool checkPassword(const QString &password);
};

#endif // AUTHENTIFICATION_H
