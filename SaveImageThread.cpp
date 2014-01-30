#include <QThread>
#include <QFile>
#include <QDebug>
#include <stdint.h>
#include <cin.h>

#include "SaveImageThread.h"

void SaveImageThread::doWork(){
  uint16_t data[CIN_DATA_FRAME_HEIGHT * CIN_DATA_FRAME_WIDTH];
  uint16_t num;
  while(1){
    cin_data_load_frame(data, &num);
    QString filename = QString("frame%1.bin").arg(num);
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write((char*)data, 2 * CIN_DATA_FRAME_HEIGHT * CIN_DATA_FRAME_WIDTH);
    file.close();
  }
}


