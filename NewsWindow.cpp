#include "NewsWindow.h"

NewsWindow::NewsWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *newsLabel = new QLabel("Latest News Updates:", this);
    layout->addWidget(newsLabel);

    QLabel *newsContent = new QLabel("No new updates.", this); // Placeholder for actual news content
    layout->addWidget(newsContent);

    setLayout(layout);
}
