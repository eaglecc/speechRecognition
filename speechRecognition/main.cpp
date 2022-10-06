#include "speechrecognition.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    speechRecognition w;
    w.show();
    return a.exec();
}
