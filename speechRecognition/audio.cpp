#include "audio.h"


audio::audio(QObject *parent)
    : QObject(parent)
{
}

audio::~audio()
{
}

void audio::startAudio(QString filename)
{
    //��ȡĬ����Ƶ�����豸
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();
    
    if (device.isNull())
    {
        //�豸������
        QMessageBox::warning(NULL,"warning","�豸������");
        return;
    }
    else
    {
        //������Ƶ�����ʽ
        QAudioFormat m_format;
        //���ò�����
        m_format.setSampleRate(16000);
        //����ͨ����
        m_format.setChannelCount(1);
        //����λ��
        m_format.setSampleSize(16);
        //���ñ����ʽ
        m_format.setCodec("audio/pcm");

        //�ж��豸�Ƿ�֧��
        if (!device.isFormatSupported(m_format))
        {
            m_format = device.nearestFormat(m_format);
        }

        //���ļ�
        m_file = new QFile();
        m_file->setFileName(filename);
        m_file->open(QIODevice::WriteOnly);

        //����¼������
        m_audioinput = new QAudioInput(m_format , this);

        //��ʼ¼��
        m_audioinput->start(m_file);

    }
   
}

void audio::stopAudio()
{
    m_audioinput->stop();
    //�ر��ļ�
    m_file->close();
    //delete m_file;
    //m_file = NULL;


}
