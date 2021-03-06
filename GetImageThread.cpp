#include <QThread>
#include <QDebug>
#include <QObject>
#include <QImage>
#include <QRgb>
#include <QVector>
#include <QDateTime>
#include "GetImageThread.h"
#include "cin.h"

GetImage::GetImage(){
    QVector<QRgb> colormap(256);

    // Make colormap for QImage

    for(int i=0;i<=255;i++){
        colormap[i] = qRgb(i,i,i);
    }

    greyColormap = colormap;

    lastFrameNo = -1;
}

void GetImage::fetchImage(void){

    // Now fetch an image from the library

    // Make a QImage

    QImage image = QImage(CIN_DATA_FRAME_WIDTH * 1.2, CIN_DATA_FRAME_HEIGHT,
                          QImage::Format_Indexed8);
    image.setColorTable(greyColormap);

    frame = cin_data_get_buffered_frame();
    int frameNo = (int)frame->number;
    QDateTime frameTimestamp;
    qint64 msecs = (frame->timestamp.tv_sec * 1000);
    msecs += (frame->timestamp.tv_usec / 1000);
    frameTimestamp.setMSecsSinceEpoch(msecs);

    if(frameNo == lastFrameNo){
        // Ok so we should just release and go!
        cin_data_release_buffered_frame();
        return;
    }

    qDebug() << "Image x = " << frame->size_x << " y = " << frame->size_y;

    // Copy this to an 8 bit QImage

    uchar *line;
    uint16_t *frame_p = frame->data;
    for(int i = 0;i<frame->size_y;i++){
        line = image.scanLine(i);
        for(int j = 0;j<frame->size_x;j++){
            line[j] = (uchar)(((*frame_p)) >> 8);
            frame_p++;
        }
    }

    cin_data_release_buffered_frame();

    lastFrameNo = frameNo;

    emit imageReady(image, frameNo, frameTimestamp);
}
