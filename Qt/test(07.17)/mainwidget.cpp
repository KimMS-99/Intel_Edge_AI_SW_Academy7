#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    // tab1
    pSocket = new Socket(ui->tab);
    ui->tab->setLayout(pSocket->layout());

    // tab2
    pSensor = new Sensor(ui->tab_2);
    ui->tab_2->setLayout(pSensor->layout());

    // tab3
    pSqlite = new Sqlite(ui->tab_3);
    ui->tab_3->setLayout(pSqlite->layout());

    ui->tabWidget->setCurrentIndex(0);

    connect(pSocket, SIGNAL(SensorRecvDataSig(QString)), pSensor, SLOT(SensorRecvDataSlot(QString)));
    connect(pSocket, SIGNAL(SqliteRecvDataSig(QString)), pSqlite, SLOT(SqliteRecvDataSlot(QString)));
}

MainWidget::~MainWidget()
{
    delete ui;
}
