#include <QThread>
#include <QDebug>
#include <QObject>
#include <QImage>
#include <QRgb>
#include <QVector>
#include "GetImageThread.h"
#include "cin.h"

GetImage::GetImage(){
    cin_init_data_port(&data_port, NULL, 0, NULL, 0, 0);
    cin_data_init(1000, 200, 0);

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

    QImage image = QImage(CIN_DATA_FRAME_WIDTH, CIN_DATA_FRAME_HEIGHT,
                          QImage::Format_Indexed8);
    image.setColorTable(greyColormap);

    frame = cin_data_get_buffered_frame();
    int frameNo = (int)frame->number;

    if(frameNo == lastFrameNo){
        // Ok so we should just release and go!
        cin_data_release_buffered_frame();
        return;
    }

    // Copy this to an 8 bit QImage

    uchar *line;
    uint16_t *frame_p = frame->data;
    for(int i = 0;i<CIN_DATA_FRAME_HEIGHT;i++){
        line = image.scanLine(i);
        for(int j = 0;j<CIN_DATA_FRAME_WIDTH;j++){
            line[j] = (uchar)(*frame_p >> 8);
            frame_p++;
        }
    }

    cin_data_release_buffered_frame();

    lastFrameNo = frameNo;

    emit imageReady(image, frameNo);
}
