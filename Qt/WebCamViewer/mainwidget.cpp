#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    pQWebEngineView = new QWebEngineView(this);
//    pQWebEngineView->load(QUrl("http://www.naver.com"));
    pQWebEngineView->load(QUrl("http://192.168.0.59:8080/?action=stream"));
    ui->pVerticalLayout->addWidget(pQWebEngineView);
}

MainWidget::~MainWidget()
{
    delete ui;
}
