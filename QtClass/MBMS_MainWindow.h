//
// Created by Van on 2025/6/14.
//

#ifndef MBMS_MAINWINDOW_H
#define MBMS_MAINWINDOW_H
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include "MBMS_LoginWidget.h"
#include "MBMS_RegisterWidget.h"
#include <QMessageBox>
#include <QCloseEvent>
#include "MBMS_AdminWidget.h"
#include "../CBack/MBMS_Library.h"
#include "../CBack/MBMS_Global.h"
class MainWindow:public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=nullptr);
    void closeEvent(QCloseEvent *event) override;
private:
    QWidget *centralWidget=new QWidget(this);
    QTextEdit *welcomeText=new QTextEdit(this);//提示文字
    QLineEdit *libTitle;
    QPushButton *generateLib;
    QPushButton *buttonLogin=new QPushButton("登录",this);//登录按钮
    LoginWidget *loginWidget;//登录界面
    QPushButton *buttonRegister=new QPushButton("注册",this);//注册按钮
    RegisterWidget *registerWidget;
};
#endif //MBMS_MAINWINDOW_H
