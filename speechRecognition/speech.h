#pragma once

#include <QObject>
#include "http.h"
const QString baidu_tokenurl = 
"https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString client_id = "GwVljoRWEAvgWNXiNgYydEqm";
const QString client_secret = "muMzoW8KUR1F6NibH2Mi1OiBuzU3GMr3";

const QString baidu_speachurl =
"http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";
class Speech : public QObject
{
    Q_OBJECT

public:
    Speech(QObject *parent = 0);
    ~Speech();
    //”Ô“Ù ∂±
    QString SpeechRecognition(QString filename);
    //Ω‚Œˆjson
    QString getJsonValue(QString key , QByteArray value);

};
