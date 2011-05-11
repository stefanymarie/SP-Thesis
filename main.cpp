#include <QtGui/QApplication>
#include "edgedetection.h"

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    edgeDetection w;
    w.show();

    return a.exec();
}
