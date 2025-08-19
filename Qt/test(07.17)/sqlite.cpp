#include "sqlite.h"
#include "ui_sqlite.h"

Sqlite::Sqlite(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sqlite)
{
    ui->setupUi(this);

    qSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    qSqlDatabase.setDatabaseName("aiot.db");
    if(qSqlDatabase.open())
        qDebug() << "Success DB Connection";
    else
        qDebug() << "Fail DB Connection";
    QString strQuery = "create table sensor_tb ("
                       "name varchar(10), "
                       "date DATETIME primary key, "
                       "illu varchar(10),"
                       "temp varchar(10),"
                       "humi varchar(10))";
    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery))
        qDebug() << "Create Table";

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
    pQDateTimeAxisX->setFormat("hh:mm");

    updateLastDateTimeSql(0);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, illuline);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, temp);
    pQChartView->chart()->setAxisX(pQDateTimeAxisX, humi);
}

void Sqlite::updateLastDateTimeSql(bool bFlag)
{
    QDateTime fromDateTime = ui->datetimeedit_1->dateTime();
    QString strFromDateTime = fromDateTime.toString("yyyy/MM/dd hh:mm:ss");
    QDateTime toDateTime = ui->datetimeedit_2->dateTime();
    QString strToDateTime = toDateTime.toString("yyyy/MM/dd hh:mm:ss");

    pQDateTimeAxisX->setRange(fromDateTime, toDateTime);
}

void Sqlite::SqliteRecvDataSlot(QString recvData)
{

    QDateTime dateTime = QDateTime::currentDateTime();

    QStringList strList = recvData.split("@");
    QString name = strList[1];
    QString illu = strList[3];
    QString tmp = strList[4];
    QString hum = strList[5];
    // qDebug() << "illu : " << illu.toInt() << "tmp : " << tmp.toFloat() << "hum : " << hum.toFloat();

    QString strQuery = "insert into sensor_tb(name, date, illu, temp, humi)"
                       "values('"+ name + "', '" + dateTime.toString("yyyy/MM/dd hh:mm:ss") + "', '" + illu + "', '" + tmp + "', '" + hum + "')";
    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery))
    {
        // qDebug() << "Insert Query Ok";
    }
}

void Sqlite::on_PbSearchDB_clicked()
{
    QDateTime fromDateTime = ui->datetimeedit_1->dateTime();
    QDateTime toDateTime = ui->datetimeedit_2->dateTime();

    ui->PbClear->clearContents();
    illuline->clear();
    temp->clear();
    humi->clear();
    ui->PbClear->setRowCount(0);

    QString strQuery = "select * from sensor_tb where '" + fromDateTime.toString("yyyy/MM/dd hh:mm:ss") + "' <= date and date <= '" + toDateTime.toString("yyyy/MM/dd hh:mm:ss") + "'";
    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery))
    {
        // qDebug() << "Select Query Ok";
        int rowCount = 0;

        QDateTime firstDateTime;
        QDateTime lastDateTime;

        while(sqlQuery.next())
        {
            rowCount++;
            ui->PbClear->setRowCount(rowCount);

            QTableWidgetItem * pQTableWidgetItemId = new QTableWidgetItem();
            QTableWidgetItem * pQTableWidgetItemDate = new QTableWidgetItem();
            QTableWidgetItem * pQTableWidgetItemIllu = new QTableWidgetItem();
            QTableWidgetItem * pQTableWidgetItemTemp = new QTableWidgetItem();
            QTableWidgetItem * pQTableWidgetItemHumi = new QTableWidgetItem();

            pQTableWidgetItemId->setText(sqlQuery.value("name").toString());
            pQTableWidgetItemDate->setText(sqlQuery.value("date").toString());
            pQTableWidgetItemIllu->setText(sqlQuery.value("illu").toString());
            pQTableWidgetItemTemp->setText(sqlQuery.value("temp").toString());
            pQTableWidgetItemHumi->setText(sqlQuery.value("humi").toString());

            ui->PbClear->setItem(rowCount-1, 0, pQTableWidgetItemId);
            ui->PbClear->setItem(rowCount-1, 1, pQTableWidgetItemDate);
            ui->PbClear->setItem(rowCount-1, 2, pQTableWidgetItemIllu);
            ui->PbClear->setItem(rowCount-1, 3, pQTableWidgetItemTemp);
            ui->PbClear->setItem(rowCount-1, 4, pQTableWidgetItemHumi);

            QDateTime sqlDateTime = QDateTime::fromString(sqlQuery.value("date").toString(), "yyyy/MM/dd hh:mm:ss");

            illuline->append(sqlDateTime.toMSecsSinceEpoch(), sqlQuery.value("illu").toInt());
            temp->append(sqlDateTime.toMSecsSinceEpoch(), sqlQuery.value("temp").toFloat());
            humi->append(sqlDateTime.toMSecsSinceEpoch(), sqlQuery.value("humi").toFloat());
        }

        sqlQuery.first();
        firstDateTime = QDateTime::fromString(sqlQuery.value("date").toString(), "yyyy/MM/dd hh:mm:ss");
        sqlQuery.last();
        lastDateTime = QDateTime::fromString(sqlQuery.value("date").toString(), "yyyy/MM/dd hh:mm:ss");
        if(firstDateTime.isValid() && lastDateTime.isValid())
        {

            pQDateTimeAxisX->setRange(firstDateTime, lastDateTime);
        } else
        {
            pQDateTimeAxisX->setRange(fromDateTime, toDateTime);
        }

        ui->PbClear->resizeColumnToContents(0);
        ui->PbClear->resizeColumnToContents(1);
        ui->PbClear->resizeColumnToContents(2);
        ui->PbClear->resizeColumnToContents(3);
        ui->PbClear->resizeColumnToContents(4);
    }
}

Sqlite::~Sqlite()
{
    delete ui;
}

void Sqlite::on_PbDeleteDB_clicked()
{
    QDateTime fromDateTime = ui->datetimeedit_1->dateTime();
    QString strFromDateTime = fromDateTime.toString("yyyy/MM/dd hh:mm:ss");
    QDateTime toDateTime = ui->datetimeedit_2->dateTime();
    QString strToDateTime = toDateTime.toString("yyyy/MM/dd hh:mm:ss");
    QString strQuery = "delete from sensor_tb where '" + strFromDateTime + "' <= date and date <= '" + strToDateTime + "'";
    QSqlQuery sqlQuery;
    if(sqlQuery.exec(strQuery))
    {
        qDebug() << "Delete Query Ok";
        illuline->clear();
        temp->clear();
        humi->clear();
        ui->PbClear->clearContents();
        ui->PbClear->setRowCount(0);
    }
}

