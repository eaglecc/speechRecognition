#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QWidget>
#include "ui_recognition.h"
#include "audio.h"
#include "speech.h"

class recognition : public QWidget
{
    Q_OBJECT

public:
    recognition(QWidget *parent = Q_NULLPTR);
    ~recognition();

public slots:
    void on_pushButton_pressed();
    void on_pushButton_released();
    void on_pushButton_clear_clicked();

private:
    Ui::recognition ui;
    audio *m_audio;
    Speech *m_speech;
};
