#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "socket.h"
#include "sensor.h"
#include "sqlite.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    Socket *pSocket; // tab1
    Sensor *pSensor; // tab2
    Sqlite *pSqlite; // tab3
};
#endif // MAINWIDGET_H
