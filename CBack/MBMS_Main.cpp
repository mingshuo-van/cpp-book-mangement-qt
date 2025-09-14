//
// Created by Van on 2025/5/30.
//
#include <QApplication>
#include "../QtClass/MBMS_MainWindow.h"
int main(int argc,char *argv[]) {
    QApplication a(argc,argv);
    MainWindow m;
    m.show();
    return a.exec();
}