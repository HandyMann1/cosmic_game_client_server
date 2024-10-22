#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include "NewsWindow.h"
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
    void toggleNewsVisibility();
    void showSettings();
    void showHelp();
    void openServerConnectionDialog();


private:
    NewsWindow *newsWindow;

};

#endif // MAINWINDOW_H
