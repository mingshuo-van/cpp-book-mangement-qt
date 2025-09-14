//
// Created by Van on 2025/6/14.
//
#include "MBMS_MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setMinimumSize(500, 400);
    setWindowTitle("我的图书管理系统");
    //设置中央控件
    setCentralWidget(centralWidget);
    //创建主布局
    QHBoxLayout *layoutText = new QHBoxLayout();
    layoutText->addWidget(welcomeText);
    QHBoxLayout *titleLayout = new QHBoxLayout();
    libTitle = new QLineEdit("友爱图书馆");
    generateLib=new QPushButton("创建图书馆");
    if (globalLibrary==nullptr) {
        globalLibrary=new Library{"友爱图书馆"};
    }
    titleLayout->addWidget(libTitle);
    titleLayout->addWidget(generateLib);
    QHBoxLayout *layoutButton = new QHBoxLayout();
    layoutButton->addWidget(buttonLogin);
    layoutButton->addWidget(buttonRegister);
    QVBoxLayout *layoutMain = new QVBoxLayout(centralWidget);
    layoutMain->addLayout(layoutText);
    layoutMain->addLayout(titleLayout);
    layoutMain->addLayout(layoutButton);
    //设置文本和按钮的signal and slot
    welcomeText->setText("欢迎使用本图书管理系统\n你可以在下方的输入栏中输入图书馆的名字\n请"
        "注意 具有相同名字的图书馆被视为同一图书馆\n不同图书馆的数据不互通\n"
        "不点击创建会默认生成一个图书馆");
    welcomeText->setReadOnly(true);
    loginWidget=new LoginWidget(this);
    connect(buttonLogin, &QPushButton::clicked, this, [this]() {
        //Library lib{libTitle->text().toStdString()};
        hide();
        loginWidget->show();
    });
    connect(loginWidget, &LoginWidget::backLast, this, [this] {
        show();
    });
    registerWidget = new RegisterWidget(this);
    connect(buttonRegister, &QPushButton::clicked, this, [this] {
        hide();
        registerWidget->show();
    });
    connect(generateLib,&QPushButton::clicked,this,[this] {
        if (globalLibrary==nullptr) {
            globalLibrary=new Library(libTitle->text().toStdString());
        }else if (globalLibrary->getTitle()!=libTitle->text().toStdString()) {
            delete globalLibrary;
            globalLibrary=new Library(libTitle->text().toStdString());
        }
        QMessageBox ::information(this,"提示","图书馆创建成功！");
    });
    connect(registerWidget,&RegisterWidget::backLast,this,[this] {
        show();
    });
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认关闭", "你确定要关闭窗口吗？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        delete globalLibrary;
        globalLibrary=nullptr;
        event->accept();
    } else {
        event->ignore();
    }
}
