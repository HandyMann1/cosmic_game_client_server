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
    QFont fonti("Cascadia Mono SemiBold", 18);
    this->setFont(fonti);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    this->resize(1200, 800);

    QPushButton *showNewsButton = new QPushButton("Show News", this);


    QPushButton *playButton = new QPushButton("Play!", this);
    QPushButton *helpButton = new QPushButton("Help", this);
    QPushButton *exitButton = new QPushButton("Exit", this);
    QPushButton *connectButton = new QPushButton("Connect to Server", this);
    QPushButton *settingsButton = new QPushButton("Settings", this);

    QWidget *playWidget = new QWidget(this);
    QWidget *newsWidget = new QWidget(this); //news screen logic here is a placeholder
    QVBoxLayout *newsLayout = new QVBoxLayout();
    QLabel *newsLabel = new QLabel("Latest News Updates:", this);
    QLabel *newsContent = new QLabel("No new updates.", this);
    QWidget *connectWidget = new QWidget(this);
    QWidget *settingsWidget = new QWidget(this);
    QWidget *helpWidget = new QWidget(this);

    QVBoxLayout *windowItself = new QVBoxLayout();
    QHBoxLayout *upperMenu = new QHBoxLayout();
    visibleScreen = new QStackedLayout();

    centralWidget->setLayout(windowItself);
    windowItself->addLayout(upperMenu);
    windowItself->addLayout(visibleScreen);

    upperMenu->addWidget(playButton);
    upperMenu->addWidget(showNewsButton);
    upperMenu->addWidget(connectButton);
    upperMenu->addWidget(settingsButton);
    upperMenu->addWidget(helpButton);
    upperMenu->addWidget(exitButton);

    visibleScreen->addWidget(playWidget);
    visibleScreen->addWidget(newsWidget);
    visibleScreen->addWidget(connectWidget);
    visibleScreen->addWidget(settingsWidget);
    visibleScreen->addWidget(helpWidget);

    newsLayout->addWidget(newsLabel);
    newsLayout->addWidget(newsContent);
    newsWidget->setLayout(newsLayout);

    connect(playButton, &QPushButton::clicked, [this]() { visibleScreen->setCurrentIndex(0); });
    connect(showNewsButton, &QPushButton::clicked, [this]() { visibleScreen->setCurrentIndex(1); });
    connect(connectButton, &QPushButton::clicked, [this]() { visibleScreen->setCurrentIndex(2); });
    connect(settingsButton, &QPushButton::clicked, [this]() { visibleScreen->setCurrentIndex(3); });
    connect(helpButton, &QPushButton::clicked, [this]() { visibleScreen->setCurrentIndex(4); });
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);
}

void MainWindow::showServerConnectionDialog(){
    ServerConnectionDialog dialog(this);
    dialog.exec();
}


