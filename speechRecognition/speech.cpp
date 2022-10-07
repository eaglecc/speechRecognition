#include "speech.h"
#include "qdebug.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonArray>
#include <QHostInfo>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>

Speech::Speech(QObject *parent)
    : QObject(parent)
{
}

Speech::~Speech()
{
}

QString Speech::SpeechRecognition(QString filename)
{
    //先获取令牌access_token的url
    QString tokenUrl = baidu_tokenurl.arg(client_id).arg(client_secret);
    //头部信息
    QMap<QString, QString> header;
    header.insert(QString("Content-Type:"),QString("audio/pcm;rate=16000"));

    //发送的数据
    QByteArray requestData;
    //返回数据
    QByteArray replyData;

    QString access_token;
    //第一次发送Http请求，获取token
    Http m_http;
    bool ret = m_http.post_sync(tokenUrl,header, requestData, replyData);
    if (ret)
    {
        QString key = "access_token";
        access_token = getJsonValue(key , replyData);
        //qDebug() << access_token;
    }
    else
    {
        return false;
    }
    //第二次发送http请求，获取语音识别结果
    QString speechurl = baidu_speachurl.arg(QHostInfo::localHostName()).arg(access_token);
    //打开音频文件将其转换为QByteArray类型
    requestData.clear();
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly);
    requestData = file.readAll();
    //qDebug() << requestData;
    file.close();
    //清除上一次答复数据
    replyData.clear();
    //第二次请求
    QString result;
    ret = m_http.post_sync(speechurl , header , requestData , replyData);
    if (ret)
    {
        //解析第二次返回的JSON数据（识别结果）
        QString key = "result";
        result = getJsonValue(key, replyData);
        qDebug() << result;
        return result;
    }
    else
    {
        QMessageBox::warning(NULL , "warning","识别失败！");
    }
}

QString Speech::getJsonValue(QString key, QByteArray value)
{
    QJsonParseError err;
    //先将value转为json文件
    QJsonDocument jsondoucument = QJsonDocument::fromJson(value,&err);
    if (err.error == QJsonParseError::NoError)
    {
        if (jsondoucument.isObject())
        {
            //将jsonDocument转换为json对象
            QJsonObject jsonobj = jsondoucument.object();
            //取出access_token
            if (jsonobj.contains(key))
            {
                QJsonValue jsonval = jsonobj.value(key);
                //如果jsonval为字符串
                if (jsonval.isString())
                {
                    return jsonval.toString();
                }
                //如果jsonval值为数组（获取的是识别结果）
                else if (jsonval.isArray())
                {
                    QJsonArray jsonarray = jsonval.toArray();
                    QJsonValue firstval = jsonarray.at(0);
                    return firstval.toString();
                }
            }
        }
    }
    return "";

}
