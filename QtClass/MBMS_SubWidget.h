//
// Created by Van on 2025/6/14.
//

#ifndef MBMS_SUBWIDGET_H
#define MBMS_SUBWIDGET_H
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include "../CBack/MBMS_Global.h"
class SubWidget:public QWidget {
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent=nullptr);
    virtual ~SubWidget();
    string getLineOne();
    string getLineTwo();
    void deleteTwoLabel();
protected:
    QLabel *label1;
    QLineEdit *line1;
    QLabel *label2;
    QLineEdit *line2;
    QPushButton *yesButton;
    QPushButton *cancelButton;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *layoutMain;
    QHBoxLayout *layoutUid;
    QHBoxLayout *layoutName;
};
#endif //MBMS_SUBWIDGET_H
