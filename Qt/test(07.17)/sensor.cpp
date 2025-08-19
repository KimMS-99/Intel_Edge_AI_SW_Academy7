#include "sensor.h"
#include "ui_sensor.h"

Sensor::Sensor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sensor)
{
    ui->setupUi(this);

    illuline = new QLineSeries(this);
    illuline->setName("조도");
    temp = new QLineSeries(this);
    temp->setName("온도");
    humi = new QLineSeries(this);
    humi->setName("습도");

    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    illuline->setPen(pen);

    pen.setWidth(2);
    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    temp->setPen(pen);

    pen.setWidth(2);
    pen.setBrush(Qt::blue);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    humi->setPen(pen);

    pQChart = new QChart();
    pQChart->addSeries(illuline);
    pQChart->addSeries(temp);
    pQChart->addSeries(humi);
    pQChart->createDefaultAxes();
    pQChart->axes(Qt::Vertical).constFirst()->setRange(0, 100);

    pQChartView = new QChartView(pQChart);
    pQChartView->setRenderHint(QPainter::Antialiasing);

    ui->ChartViewLayout->layout()->addWidget(pQChartView);
    pQDateTimeAxisX = new QDateTimeAxis;
    pQDateTimeAxisX->setFormat("hh:mm:ss");

    updateLastDateTime(0);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, illuline);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, temp);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, humi);
}

Sensor::~Sensor()
{
    delete ui;
}

void Sensor::on_PbClear_clicked()
{
    illuline->clear();
    temp->clear();
    humi->clear();
    updateLastDateTime(0);
}

void Sensor::updateLastDateTime(bool bFlag)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    firstDateTime.setDate(date);
    firstDateTime.setTime(time);

    lastDateTime.setDate(date);
    QTime tempTime = time.addSecs(10);
    lastDateTime.setTime(tempTime);

    pQDateTimeAxisX->setRange(firstDateTime, lastDateTime);
}

void Sensor::SensorRecvDataSlot(QString recvData)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QDateTime xValue;
    xValue.setDate(date);
    xValue.setTime(time);

    // qDebug() << "recvData : " << recvData;

    QStringList strList = recvData.split("@");
    QString illu = strList[3]; // 조도
    QString tmp = strList[4]; // 온도
    QString hum = strList[5]; // 습도
    // qDebug() << "illu : " << illu.toInt() << "tmp : " << tmp.toInt() << "hum : " << hum.toInt();

    if(xValue >= lastDateTime)
    {
        qDebug() << "time";
        QTime tempTime = time.addSecs(10);
        lastDateTime.setTime(tempTime);
        pQDateTimeAxisX->setRange(firstDateTime, lastDateTime);
    }
    illuline->append(xValue.toMSecsSinceEpoch(), illu.toInt());
    temp->append(xValue.toMSecsSinceEpoch(), tmp.toDouble());
    humi->append(xValue.toMSecsSinceEpoch(), hum.toDouble());
}
