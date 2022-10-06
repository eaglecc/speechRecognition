#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_speechrecognition.h"

class speechRecognition : public QMainWindow
{
    Q_OBJECT

public:
    speechRecognition(QWidget *parent = Q_NULLPTR);

private:
    Ui::speechRecognitionClass ui;
};
