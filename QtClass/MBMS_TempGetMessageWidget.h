//
// Created by Van on 2025/6/16.
//

#ifndef MBMS_TEMPGETMESSAGEWIDGET_H
#define MBMS_TEMPGETMESSAGEWIDGET_H
#include "MBMS_SubWidget.h"
#include <string>
class TempGetMessageWidget:public SubWidget {
public:
    TempGetMessageWidget(QWidget *parent=nullptr);
    void setLabelOne(const string_view str);
    void setLabelTwo(const string_view str);
    void setTextEdit(const string_view massage);
    QPushButton *getYesButton();
    QPushButton *getCancelButton();

private:
    string first;
    string second;
    QTextEdit *point;
};
#endif //MBMS_TEMPGETMESSAGEWIDGET_H
