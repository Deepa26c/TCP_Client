#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    pClientSocket = new QTcpSocket(this);
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButtonConnect_clicked()
{
    pClientSocket->connectToHost(ui->textEditIP->toPlainText(),quint16(ui->textEditMessage->toPlainText().toInt()));
    connect(pClientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

}

void Dialog::on_pushButtonSend_clicked()
{
    QString message = ui->textEditMessage->toPlainText().trimmed();
    if(!message.isEmpty())
    {
        pClientSocket->write(QString(message + "\n").toUtf8());
    }

    ui->textEditMessage->clear();

    ui->textEditMessage->setFocus();
}

void Dialog::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
            break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this,tr("Client"),tr("Host not found"));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this,tr("Client"),tr("Connection is refused by server, check server is connected"));
        break;
    default:
        QMessageBox::information(this,tr("Client"),tr("Error occure: 1").arg(pClientSocket->errorString()));


    }
}
