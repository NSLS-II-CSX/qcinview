#ifndef GETIMAGETHREAD_H
#define GETIMAGETHREAD_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include <QImage>
#include <QRgb>
#include <QVector>
#include <QDateTime>

#include "cin.h"

typedef struct cin_port cin_port_t;
typedef struct cin_data_frame cin_data_frame_t;

class GetImage : public QObject
 {
     Q_OBJECT
     QThread getImageThread;
 public:
     GetImage();
 private:
     cin_port_t data_port;
     cin_data_frame_t *frame;
     QVector<QRgb> greyColormap;
     int lastFrameNo;
 public slots:
     void fetchImage(void);
 signals:
     void imageReady(QImage image, int imageNumber, QDateTime timestamp);
 };

class GetImageController : public QObject
 {
     Q_OBJECT
     QThread getImageThread;
 public:
     GetImageController(){
        GetImage *getImage = new GetImage();
        getImage->moveToThread(&getImageThread);
        connect(&getImageThread, SIGNAL(finished()), getImage, SLOT(deleteLater()));
        connect(getImage, SIGNAL(imageReady(QImage, int, QDateTime)), 
                this, SLOT(updateImage(QImage, int, QDateTime)));
        connect(&timer, SIGNAL(timeout()), getImage, SLOT(fetchImage(void)));
        getImageThread.start();

        // Now start timer.

        timer.start(50);
     }
     ~GetImageController(){
         getImageThread.quit();
         getImageThread.wait();
     }
     QTimer timer;
 public slots:
     void updateImage(QImage image, int imageNumber, QDateTime timestamp){
         emit newImage(image, imageNumber, timestamp);
     }
 signals:
     void newImage(QImage image, int imageNumber, QDateTime timestamp);
 };

#endif // GETIMAGETHREAD_H
