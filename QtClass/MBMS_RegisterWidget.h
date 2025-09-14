//
// Created by Van on 2025/6/15.
//

#ifndef MBMS_REGISTERWIDGET_H
#define MBMS_REGISTERWIDGET_H
#include "MBMS_SubWidget.h"
#include "../CBack/MBMS_Global.h"
class RegisterWidget:public SubWidget {
    Q_OBJECT
public:
    RegisterWidget(QWidget *parent=nullptr);
    signals:void backLast();
};
#endif //MBMS_REGISTERWIDGET_H
