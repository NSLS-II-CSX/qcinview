#include <QDebug>
#include <QImage>
#include <QScrollArea>
#include <QPalette>
#include <QDateTime>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GetImageThread.h"
#include "statuswidget.h"
#include <cin.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scrollArea = new QScrollArea(this);
    imageLabel = new QLabel();
    imageLabel->setGeometry(0,0,CIN_DATA_FRAME_WIDTH,CIN_DATA_FRAME_HEIGHT);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    statusWidget = new StatusWidget(this);
    statusWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, statusWidget);

    getImageThread = new GetImageController();

    statusTimer = new QTimer();

    connect(getImageThread, SIGNAL(newImage(QImage, int, QDateTime)), 
            this, SLOT(updateImage(QImage, int, QDateTime)));
    connect(statusTimer, SIGNAL(timeout()), statusWidget, SLOT(updateStatus()));

    statusTimer->start(250);

    statusBar()->showMessage(tr("Ready"));

}

void MainWindow::updateImage(QImage image, int imageNumber, QDateTime timestamp){
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->update();
    statusBar()->showMessage(QString("Displaying image %1 arrived at %2").arg(imageNumber).arg(timestamp.toString("dd:MM:yyyy hh:mm:ss.zzz")));
}

MainWindow::~MainWindow()
{
    delete getImageThread;
    delete ui;
    cin_data_stop_threads();
    cin_data_wait_for_threads();
}
