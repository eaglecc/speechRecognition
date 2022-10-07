#include "recognition.h"
#include "qdebug.h"
#include <QPushButton>

recognition::recognition(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    //qDebug() << connect(ui.pushButton , &QPushButton::pressed , this , &recognition::on_pushButton_pressed);
    //qDebug() << connect(ui.pushButton , &QPushButton::released , this , &recognition::on_pushButton_released);
    ui.pushButton->setText("按住说话");
}

recognition::~recognition()
{
}

void recognition::on_pushButton_released()
{
    ui.pushButton->setText("开始识别");

    //停止录音
    m_audio->stopAudio();

    //开始识别
    m_speech = new Speech();
    QString resulttext;
    resulttext = m_speech->SpeechRecognition("C:\\Users\\chengyuchao\\Desktop\\audio\\demo.pcm");
    ui.textEdit->setText(resulttext);
    ui.pushButton->setText("按住说话");
}

void recognition::on_pushButton_clear_clicked()
{
    ui.textEdit->clear();
}

void recognition::on_pushButton_pressed() {
    ui.pushButton->setText("松开识别");
    //开始录音
    m_audio = new audio();
    m_audio->startAudio("C:\\Users\\chengyuchao\\Desktop\\audio\\demo.pcm");
    
}