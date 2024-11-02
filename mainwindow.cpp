#include "MainWindow.h"

ServerConnectionDialog::ServerConnectionDialog(QWidget *parent) : QDialog(parent){

    setWindowTitle("Connect to Server");
    QFormLayout *layout = new QFormLayout(this);

    QLabel *serverLabel = new QLabel("Server Address:", this);
    QLineEdit *serverLineEdit = new QLineEdit(this);

    layout->addRow(serverLabel, serverLineEdit);

    QPushButton *connectButton = new QPushButton("Connect", this);
    layout->addRow(connectButton);

    connect(connectButton, &QPushButton::clicked, this, &ServerConnectionDialog::accept);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    this->resize(1200, 800);

    QPushButton *showNewsButton = new QPushButton("Show News", this);
    newsWindow = new NewsWindow(this);


    QPushButton *playButton = new QPushButton("Play!", this);
    QPushButton *helpButton = new QPushButton("Help", this);
    QPushButton *exitButton = new QPushButton("Exit", this);
    QPushButton *connectButton = new QPushButton("Connect to Server", this);
    QPushButton *settingsButton = new QPushButton("Settings", this);

    QGridLayout *gridLayout = new QGridLayout(centralWidget);

    gridLayout->addWidget(showNewsButton, 0, 0);
    gridLayout->addWidget(newsWindow, 1, 0);
    gridLayout->addWidget(playButton, 2, 0);

    gridLayout->addWidget(settingsButton, 0, 1);
    gridLayout->addWidget(helpButton, 1, 1);

    gridLayout->addWidget(exitButton, 0, 2);
    gridLayout->addWidget(connectButton, 2, 1);

    connect(showNewsButton, &QPushButton::clicked, this, &MainWindow::toggleNewsVisibility);

    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::showSettings);
    connect(helpButton, &QPushButton::clicked, this, &MainWindow::showHelp);

    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);

    connect(connectButton, &QPushButton::clicked, this, &MainWindow::openServerConnectionDialog);
}

void MainWindow::toggleNewsVisibility() {
    if (newsWindow->isVisible()) {
        newsWindow->hide();
    } else {
        newsWindow->show();
    }
}
void MainWindow::showSettings(){
    //implement some settings
}
void MainWindow::showHelp(){
    //implement some help or advices
}
void MainWindow::openServerConnectionDialog(){
    ServerConnectionDialog dialog(this);
    dialog.exec();
}


