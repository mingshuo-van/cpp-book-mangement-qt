//
// Created by Van on 2025/6/15.
//

#ifndef MBMS_COMMONUSERWIDGET_H
#define MBMS_COMMONUSERWIDGET_H
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <vector>
#include <QCloseEvent>
#include "../CBack/MBMS_Global.h"
class CommonUserWidget:public QWidget {
    Q_OBJECT
public:
    CommonUserWidget(QWidget *parent=nullptr);
    void closeEvent(QCloseEvent *event) override;
    signals: void backLogin();
protected:
    std::vector<QPushButton*> v{8};
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *mainLayout;
};
#endif //MBMS_COMMONUSERWIDGET_H
