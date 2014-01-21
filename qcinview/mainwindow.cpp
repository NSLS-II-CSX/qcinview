#include <QDebug>
#include <QImage>
#include <QScrollArea>
#include <QPalette>
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

    connect(getImageThread, SIGNAL(newImage(QImage, int)), this, SLOT(updateImage(QImage, int)));
    connect(statusTimer, SIGNAL(timeout()), statusWidget, SLOT(updateStatus()));

    statusTimer->start(500);

    statusBar()->showMessage(tr("Ready"));

}

void MainWindow::updateImage(QImage image, int imageNumber){
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->update();
    statusBar()->showMessage(QString("Displaying image %1").arg(imageNumber));
}

MainWindow::~MainWindow()
{
    delete getImageThread;
    delete ui;
}
