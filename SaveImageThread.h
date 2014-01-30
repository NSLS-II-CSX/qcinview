#include <QThread>
#include <QObject>
#include <cin.h>

class SaveImageThread : public QObject {
  Q_OBJECT
public slots:
  void doWork();
};


