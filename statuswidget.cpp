#include "statuswidget.h"
#include "ui_statuswidget.h"
#include "cin.h"

StatusWidget::StatusWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::StatusWidget)
{
    ui->setupUi(this);
}

StatusWidget::~StatusWidget()
{
    delete ui;
}

void StatusWidget::updateStatus(void){
    stats = cin_data_get_stats();
    ui->droppedPacketsLabel->setText(QString("%1").arg(stats.dropped_packets));
    ui->frameNumberLabel->setText(QString("%1").arg(stats.last_frame));
    ui->framerateLabel->setText(QString("%1s^-1").arg(stats.framerate));
    ui->packetFifoBar->setValue(stats.packet_percent_full);
    ui->frameFifoBar->setValue(stats.frame_percent_full);
    ui->imageFifoBar->setValue(stats.image_percent_full);
    ui->packetOverruns->setText(QString("%1").arg(stats.packet_overruns));
    ui->frameOverruns->setText(QString("%1").arg(stats.frame_overruns));
    ui->imageOverruns->setText(QString("%1").arg(stats.image_overruns));
}
