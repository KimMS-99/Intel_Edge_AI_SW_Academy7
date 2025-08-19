#ifndef SQLITE_H
#define SQLITE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QTableWidgetItem>

#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
QT_CHARTS_USE_NAMESPACE
#endif
namespace Ui {
class Sqlite;
}

class Sqlite : public QWidget
{
    Q_OBJECT

public:
    explicit Sqlite(QWidget *parent = nullptr);
    ~Sqlite();

private:
    Ui::Sqlite *ui;

    QSqlDatabase qSqlDatabase;
    QLineSeries * illuline;
    QLineSeries * humi;
    QLineSeries * temp;
    QChart * pQChart;
    QChartView * pQChartView;
    QDateTimeAxis *pQDateTimeAxisX;

    void updateLastDateTimeSql(bool);

private slots:
    void SqliteRecvDataSlot(QString);
    void on_PbSearchDB_clicked();
    void on_PbDeleteDB_clicked();
};

#endif // SQLITE_H
