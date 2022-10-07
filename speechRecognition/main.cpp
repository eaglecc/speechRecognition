#include "speechrecognition.h"
#include <QtWidgets/QApplication>
#include "recognition.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*speechRecognition w;
    w.show();*/
    recognition r;
    r.show();
    return a.exec();
}
