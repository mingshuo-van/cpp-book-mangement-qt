//
// Created by Van on 2025/6/18.
//

#ifndef MBMS_ADMINWIDGET_H
#define MBMS_ADMINWIDGET_H
#include "MBMS_CommonUserWidget.h"
class AdminWidget:public CommonUserWidget {
public:
    AdminWidget(QWidget *parent=nullptr);
private:
    vector<QPushButton*> v{5};
    QHBoxLayout *attachedLayout;
};
#endif //MBMS_ADMINWIDGET_H
