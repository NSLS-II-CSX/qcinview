#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QImage>
#include <QScrollArea>
#include <QLabel>
#include <QDateTime>
#include "GetImageThread.h"
#include "statuswidget.h"
#include "cin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void updateImage(QImage image, int imageNumber, QDateTime timestamp);

private:
    Ui::MainWindow *ui;
    struct cin_port data_port;
    GetImageController *getImageThread;
    StatusWidget *statusWidget;
    QScrollArea *scrollArea;
    QLabel *imageLabel;
    QTimer *statusTimer;
};

#endif // MAINWINDOW_H
