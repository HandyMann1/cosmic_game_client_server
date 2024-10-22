#ifndef NEWSWINDOW_H
#define NEWSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class NewsWindow : public QWidget {
public:
    explicit NewsWindow(QWidget *parent = nullptr);
};

#endif // NEWSWINDOW_H
