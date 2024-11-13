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
    //NewsWindow *newsWindow;
    QStackedLayout *visibleScreen;

};

#endif // MAINWINDOW_H
