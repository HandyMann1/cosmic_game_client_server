#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QWidget>
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QStackedLayout>
#include <QComboBox>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QMessageBox>

class ServerConnectionDialog : public QDialog {
    Q_OBJECT
public:
    explicit ServerConnectionDialog(QWidget *parent = nullptr);
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void showServerConnectionDialog();

private:
    void updateNews();
    QStackedLayout *visibleScreen;
    QLabel *newsContent;

};

#endif // MAINWINDOW_H
