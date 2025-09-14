//
// Created by Van on 2025/6/19.
//

#ifndef MBMS_CHECKBOOK_H
#define MBMS_CHECKBOOK_H
#include  "MBMS_TempGetMessageWidget.h"
class CheckBook:public TempGetMessageWidget {
public:
    CheckBook(QWidget *parent=nullptr);
    string getAuthor();
    int getTotalCount();
    double getPrice();
private:
    QLabel* label[3];
    QLineEdit* line[3];
    QHBoxLayout* layout[3];
};
#endif //MBMS_CHECKBOOK_H
