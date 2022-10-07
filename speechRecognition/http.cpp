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
    //执行发送请求动作
    QNetworkAccessManager manager;
    //创建请求对象，整合url和header
    QNetworkRequest request;
    request.setUrl(url);
    //遍历header
    QMapIterator<QString, QString> iter(header);
    while (iter.hasNext())
    {
        iter.next();
        request.setRawHeader(iter.key().toLatin1(),iter.value().toLatin1());
    }
    QNetworkReply *reply = manager.post(request,requestData);
    //等待服务器返回
    QEventLoop loop;
    connect(reply , &QNetworkReply::finished ,&loop , &QEventLoop::quit);
    loop.exec();

    //qDebug() << "QSslSocket=" << QSslSocket::sslLibraryBuildVersionString();
    //qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();
    if (reply!= nullptr && reply->error() == QNetworkReply::NoError)
    {
        replyData = reply->readAll();
        //qDebug() << replyData;
        return true;
    }
    else
    {
        qDebug() << "请求失败";
        return false;
    }


}
