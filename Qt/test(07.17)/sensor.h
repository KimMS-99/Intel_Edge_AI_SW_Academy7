#ifndef SENSOR_H
#define SENSOR_H

#include <QWidget>
#include <QTime>
#include <QDate>
#include <QDebug>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
QT_CHARTS_USE_NAMESPACE
#endif

namespace Ui {
class Sensor;
}

class Sensor : public QWidget
{
    Q_OBJECT

public:
    explicit Sensor(QWidget *parent = nullptr);
    ~Sensor();

private:
    Ui::Sensor *ui;

    QLineSeries * illuline;
    QLineSeries * humi;
    QLineSeries * temp;
    QChart * pQChart;
    QChartView * pQChartView;
    QDateTimeAxis *pQDateTimeAxisX;
    QDateTime firstDateTime;
    QDateTime lastDateTime;

    void updateLastDateTime(bool);

private slots:
    void SensorRecvDataSlot(QString);
    void on_PbClear_clicked();
};

#endif // SENSOR_H
