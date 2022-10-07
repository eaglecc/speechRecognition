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
    //获取默认音频输入设备
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();
    
    if (device.isNull())
    {
        //设备不存在
        QMessageBox::warning(NULL,"warning","设备不存在");
        return;
    }
    else
    {
        //设置音频编码格式
        QAudioFormat m_format;
        //设置采样率
        m_format.setSampleRate(16000);
        //设置通道数
        m_format.setChannelCount(1);
        //设置位深
        m_format.setSampleSize(16);
        //设置编码格式
        m_format.setCodec("audio/pcm");

        //判断设备是否支持
        if (!device.isFormatSupported(m_format))
        {
            m_format = device.nearestFormat(m_format);
        }

        //打开文件
        m_file = new QFile();
        m_file->setFileName(filename);
        m_file->open(QIODevice::WriteOnly);

        //创建录音对象
        m_audioinput = new QAudioInput(m_format , this);

        //开始录音
        m_audioinput->start(m_file);

    }
   
}

void audio::stopAudio()
{
    m_audioinput->stop();
    //关闭文件
    m_file->close();
    //delete m_file;
    //m_file = NULL;


}
