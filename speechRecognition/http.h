#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QObject>
#include <QMap>
#include <QByteArray>

class Http : public QObject
{
    Q_OBJECT

public:
    Http(QObject *parent = 0);
    ~Http();

    //∑¢ÀÕhttp«Î«Û
    bool post_sync(QString url , QMap<QString , QString> header ,QByteArray requestData ,QByteArray &replyData);

};
