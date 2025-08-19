#ifndef SOCKET_H
#define SOCKET_H

#include <QWidget>
#include <QDebug>
#include <QTime>
#include <QLineEdit>
#include <QDebug>

#include "keyboard.h"
#include "sockclient.h"

namespace Ui {
class Socket;
}

class Socket : public QWidget
{
    Q_OBJECT

public:
    explicit Socket(QWidget *parent = nullptr);
    ~Socket();
    SockClient * getSockClient();

private slots:
    void updateRecvDataSlot(QString);
    void on_PbServerCon_toggled(bool checked);

    void on_PbRecvDel_clicked();

    void on_PbSend_clicked();

    void on_PleRecvId_selectionChanged();

    void on_PleSendData_selectionChanged();

signals:
    void SensorRecvDataSig(QString);
    void SqliteRecvDataSig(QString);

private:
    Ui::Socket *ui;

    SockClient *pSockClient;
    Keyboard *pKeyboard;
};

#endif // SOCKET_H
