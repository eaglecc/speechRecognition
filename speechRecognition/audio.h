#pragma once

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QMessageBox>
#include <QFile>
#include <QAudioInput>

class audio : public QObject
{
    Q_OBJECT

public:
    audio(QObject *parent = 0);
    ~audio();
    //��ʼ¼��
    void startAudio(QString filename);
    //ֹͣ¼��
    void stopAudio();

private:
    QFile *m_file;
    QAudioInput *m_audioinput;
};
