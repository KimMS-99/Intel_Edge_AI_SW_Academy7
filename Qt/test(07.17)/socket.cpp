#include "socket.h"
#include "ui_socket.h"

Socket::Socket(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Socket)
{
    ui->setupUi(this);

    ui->PbRecvDel->setEnabled(false);

    pSockClient = new SockClient(this);
    pKeyboard = new Keyboard();

    connect(pSockClient, SIGNAL(socketRevcDataSig(QString)), this, SLOT(updateRecvDataSlot(QString)));
    // on_PbServerCon_toggled(true);
}

Socket::~Socket()
{
    delete ui;
}

void Socket::on_PbServerCon_toggled(bool checked)
{
    bool bFlag;
    qDebug() << "on_PbServerCon_toggled";
    if(checked)
    {
        pSockClient->connectToServerSlot(bFlag);
        if(bFlag)
        {
            ui->PbServerCon->setText("서버 해제");
            ui->PbRecvDel->setEnabled(true);
        }
    }
    else
    {
        pSockClient->socketClosedServerSlot();
        ui->PbServerCon->setText("서버 연결");
        ui->PbRecvDel->setEnabled(false);
    }
}

void Socket::updateRecvDataSlot(QString strRecvData)
{
    strRecvData.chop(1);
    QTime time = QTime::currentTime();
    QString strTime = time.toString();
    strTime = strTime + " " + strRecvData;
    ui->textEdit->append(strTime);

    strRecvData.replace("[", "@");
    strRecvData.replace("]", "@");

    QStringList strList = strRecvData.split("@");

    // qDebug() << strList;

    if(strList[2].indexOf("SENSOR") == 0)
    {
        qDebug() << "Sensor";
        emit SensorRecvDataSig(strRecvData);
        emit SqliteRecvDataSig(strRecvData);
    }
}


void Socket::on_PbRecvDel_clicked()
{
    ui->textEdit->clear();
}


void Socket::on_PbSend_clicked()
{
    QString strRecvId = ui->PleRecvId->text();
    QString strSendData = ui->PleSendData->text();

    qDebug() << strRecvId;
    qDebug() << strSendData;

    if(strRecvId.isEmpty())
    {
        strSendData = "[ALLMSG]" + strSendData;
    }
    else
    {
        strSendData = "[" + strRecvId + "]" + strSendData;
    }
    pSockClient->socketWriteDataSlot(strSendData);
    ui->PleSendData->clear();
}

SockClient * Socket::getSockClient()
{
    return pSockClient;
}

void Socket::on_PleRecvId_selectionChanged()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyboard->setLineEdit(pQLineEdit);
    pKeyboard->show();
}

void Socket::on_PleSendData_selectionChanged()
{
    QLineEdit *pQLineEdit = (QLineEdit *)sender();
    pKeyboard->setLineEdit(pQLineEdit);
    pKeyboard->show();
}

