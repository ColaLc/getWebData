#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();


private slots:
    void on_pushButton_clicked();
     void finishedSlot(QNetworkReply*);

private:
    Ui::Dialog *ui;
    QNetworkAccessManager *m_NetManger;
    QNetworkReply* m_Reply;
};

#endif // DIALOG_H
