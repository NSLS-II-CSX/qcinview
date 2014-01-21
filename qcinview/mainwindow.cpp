#include <QDebug>
#include <QImage>
#include <QScrollArea>
#include <QPalette>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GetImageThread.h"
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

    getImageThread = new GetImageController();

    connect(getImageThread, SIGNAL(newImage(QImage, int)), this, SLOT(updateImage(QImage, int)));

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
