#include "http.h"
#include "qdebug.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QEventLoop>

Http::Http(QObject *parent)
    : QObject(parent)
{
}

Http::~Http()
{
}

bool Http::post_sync(QString url, QMap<QString, QString> header, QByteArray requestData, QByteArray & replyData)
{
    //ִ�з���������
    QNetworkAccessManager manager;
    //���������������url��header
    QNetworkRequest request;
    request.setUrl(url);
    //����header
    QMapIterator<QString, QString> iter(header);
    while (iter.hasNext())
    {
        iter.next();
        request.setRawHeader(iter.key().toLatin1(),iter.value().toLatin1());
    }
    QNetworkReply *reply = manager.post(request,requestData);
    //�ȴ�����������
    QEventLoop loop;
    connect(reply , &QNetworkReply::finished ,&loop , &QEventLoop::quit);
    loop.exec();

    //qDebug() << "QSslSocket=" << QSslSocket::sslLibraryBuildVersionString();
    //qDebug() << "OpenSSL֧�����:" << QSslSocket::supportsSsl();
    if (reply!= nullptr && reply->error() == QNetworkReply::NoError)
    {
        replyData = reply->readAll();
        //qDebug() << replyData;
        return true;
    }
    else
    {
        qDebug() << "����ʧ��";
        return false;
    }


}
