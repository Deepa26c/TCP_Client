#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QTcpSocket *pClientSocket;
private slots:
    void displayError(QAbstractSocket::SocketError socketError);

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
