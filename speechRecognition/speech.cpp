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
    //�Ȼ�ȡ����access_token��url
    QString tokenUrl = baidu_tokenurl.arg(client_id).arg(client_secret);
    //ͷ����Ϣ
    QMap<QString, QString> header;
    header.insert(QString("Content-Type:"),QString("audio/pcm;rate=16000"));

    //���͵�����
    QByteArray requestData;
    //��������
    QByteArray replyData;

    QString access_token;
    //��һ�η���Http���󣬻�ȡtoken
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
    //�ڶ��η���http���󣬻�ȡ����ʶ����
    QString speechurl = baidu_speachurl.arg(QHostInfo::localHostName()).arg(access_token);
    //����Ƶ�ļ�����ת��ΪQByteArray����
    requestData.clear();
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly);
    requestData = file.readAll();
    //qDebug() << requestData;
    file.close();
    //�����һ�δ�����
    replyData.clear();
    //�ڶ�������
    QString result;
    ret = m_http.post_sync(speechurl , header , requestData , replyData);
    if (ret)
    {
        //�����ڶ��η��ص�JSON���ݣ�ʶ������
        QString key = "result";
        result = getJsonValue(key, replyData);
        qDebug() << result;
        return result;
    }
    else
    {
        QMessageBox::warning(NULL , "warning","ʶ��ʧ�ܣ�");
    }
}

QString Speech::getJsonValue(QString key, QByteArray value)
{
    QJsonParseError err;
    //�Ƚ�valueתΪjson�ļ�
    QJsonDocument jsondoucument = QJsonDocument::fromJson(value,&err);
    if (err.error == QJsonParseError::NoError)
    {
        if (jsondoucument.isObject())
        {
            //��jsonDocumentת��Ϊjson����
            QJsonObject jsonobj = jsondoucument.object();
            //ȡ��access_token
            if (jsonobj.contains(key))
            {
                QJsonValue jsonval = jsonobj.value(key);
                //���jsonvalΪ�ַ���
                if (jsonval.isString())
                {
                    return jsonval.toString();
                }
                //���jsonvalֵΪ���飨��ȡ����ʶ������
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
