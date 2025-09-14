//
// Created by Van on 2025/6/14.
//

#ifndef MBMS_LOGINWIDGET_H
#define MBMS_LOGINWIDGET_H
#include "MBMS_SubWidget.h"
#include "MBMS_CommonUserWidget.h"
#include "MBMS_AdminWidget.h"
#include "../CBack/MBMS_Global.h"
class LoginWidget:public SubWidget {
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent=nullptr);
    signals: void backLast();
private:
    CommonUserWidget *commonUserWidget;
    AdminWidget *adminWidget;
};
#endif //MBMS_LOGINWIDGET_H
