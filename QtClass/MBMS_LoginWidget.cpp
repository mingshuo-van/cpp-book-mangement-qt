//
// Created by Van on 2025/6/14.
//
#include "MBMS_LoginWidget.h"

#include "MBMS_MainWindow.h"
LoginWidget::LoginWidget(QWidget *parent):SubWidget(parent) {
    label1->setText("uid:");
    label2->setText("name:");
    yesButton->setText("确定");
    cancelButton->setText("取消");
    setWindowTitle("普通用户和管理员登录界面");
    commonUserWidget=new CommonUserWidget(this);
    adminWidget=new AdminWidget(this);
    connect(cancelButton,&QPushButton::clicked,this,[this] {
        emit backLast();
        hide();
    });
    connect(yesButton,&QPushButton::clicked,this,[this] {
        string uid=line1->text().toStdString();
        string name=line2->text().toStdString();
        if (globalLibrary==nullptr) {
            //如果没有创建/选择图书馆
            QMessageBox::information(this,"警告","图书馆未创建！");
            return;
        }
        if (globalLibrary->getUser(uid)==
            globalLibrary->getNotExistUser()||globalLibrary->getUser(uid)->getName()!=name) {
            //如果用户不存在或如果用户名不正确
            QMessageBox::information(this,"警告","用户不存在或用户名错误！");
            return;
        }
        globalUserUid=uid;
        globalUserName=name;
        globalUser=globalLibrary->getUser(uid);
        hide();
        AdminUser *u=dynamic_cast<AdminUser *>(globalUser);
        if (u==nullptr)
            commonUserWidget->show();
        else
            adminWidget->show();
    });
    connect(commonUserWidget,&CommonUserWidget::backLogin,this,[this] {
        line1->clear();
        line2->clear();
        show();
    });
    connect(adminWidget,&CommonUserWidget::backLogin,this,[this] {
        line1->clear();
        line2->clear();
        show();
    });
}
