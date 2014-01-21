#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QDockWidget>
#include <cin.h>

namespace Ui {
class StatusWidget;
}

class StatusWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit StatusWidget(QWidget *parent = 0);
    ~StatusWidget();
public slots:
    void updateStatus(void);
    
private:
    Ui::StatusWidget *ui;
    struct cin_data_stats stats;
};

#endif // STATUSWIDGET_H
