#include "recognition.h"
#include "qdebug.h"
#include <QPushButton>

recognition::recognition(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    //qDebug() << connect(ui.pushButton , &QPushButton::pressed , this , &recognition::on_pushButton_pressed);
    //qDebug() << connect(ui.pushButton , &QPushButton::released , this , &recognition::on_pushButton_released);
    ui.pushButton->setText("��ס˵��");
}

recognition::~recognition()
{
}

void recognition::on_pushButton_released()
{
    ui.pushButton->setText("��ʼʶ��");

    //ֹͣ¼��
    m_audio->stopAudio();

    //��ʼʶ��
    m_speech = new Speech();
    QString resulttext;
    resulttext = m_speech->SpeechRecognition("C:\\Users\\chengyuchao\\Desktop\\audio\\demo.pcm");
    ui.textEdit->setText(resulttext);
    ui.pushButton->setText("��ס˵��");
}

void recognition::on_pushButton_clear_clicked()
{
    ui.textEdit->clear();
}

void recognition::on_pushButton_pressed() {
    ui.pushButton->setText("�ɿ�ʶ��");
    //��ʼ¼��
    m_audio = new audio();
    m_audio->startAudio("C:\\Users\\chengyuchao\\Desktop\\audio\\demo.pcm");
    
}