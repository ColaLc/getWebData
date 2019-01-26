#include "dialog.h"
#include "ui_dialog.h"
#include <qdebug.h>
#include <QFile>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QUrl url("https://search.51job.com/list/000000,000000,0000,00,9,99,%25E8%25BD%25AF%25E4%25BB%25B6%25E6%25B5%258B%25E8%25AF%2595%25E5%25B7%25A5%25E7%25A8%258B%25E5%25B8%2588,2,1.html?lang=c&stype=&postchannel=0000&workyear=99&cotype=99&degreefrom=99&jobterm=99&companysize=99&providesalary=99&lonlat=0%2C0&radius=-1&ord_field=0&confirmdate=9&fromType=&dibiaoid=0&address=&line=&specialarea=00&from=&welfare=");
    //QUrl url("http://www.suse.edu.cn/");
    m_NetManger = new QNetworkAccessManager();
    m_Reply = m_NetManger->get(QNetworkRequest(QUrl(url)));
    connect(m_NetManger, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSlot(QNetworkReply*)));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{

}

void Dialog::finishedSlot(QNetworkReply *)
{
    /******************文件读写***********************/

//    QFile data("E:/Code/QT_code/readFile/testfile.txt");  //读
//    if(!data.open(QFile::ReadOnly | QFile::Text))
//        qDebug()<<"Can not open";//打开文件
//    QTextStream in(&data);
//    QString data1 = in.readAll();


    QFile file("E:/Code/QT_code/readFile/testfile.txt");
    if (m_Reply->error() == QNetworkReply::NoError)
    {
//        QByteArray bytes = m_Reply->readAll();
//        QString string = QString::fromUtf8(bytes);
        file.open(QFile::WriteOnly | QFile::Text);  //写  ps：若要非连续写入 ||QIODevice::Append
        QTextStream in(&file);
        in<<m_Reply->readAll();
        QMessageBox::information(this,tr("提示"),tr("网站数据获取成功！"),QMessageBox::Ok);
    }
    else
    {
        qDebug()<< m_Reply->errorString();
        QMessageBox::information(this,tr("提示"),tr("网站数据获取失败！"),QMessageBox::Ok);
    }
    file.close();
    if(file.size()<10)
        file.remove();
    m_Reply->deleteLater();

}
