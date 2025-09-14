//
// Created by Van on 2025/6/15.
//
#include "MBMS_RegisterWidget.h"

#include <QCloseEvent>
#include <QMessageBox>

RegisterWidget::RegisterWidget(QWidget *parent):SubWidget(parent) {
    setWindowTitle("普通用户注册界面");
    yesButton->setText("注册");
    cancelButton->setText("取消");
    label1->setText("uid:");
    label2->setText("name:");
    connect(yesButton,&QPushButton::clicked,this,[this] {
        User *u=new User(getLineOne(),getLineTwo());
        QMessageBox::information(this,"提醒",globalLibrary->addUser(u).data());
        emit backLast();
        line1->clear();
        line2->clear();
        hide();
    });
    connect(cancelButton,&QPushButton::clicked,this,[this] {
        emit backLast();
        hide();
    });
}
