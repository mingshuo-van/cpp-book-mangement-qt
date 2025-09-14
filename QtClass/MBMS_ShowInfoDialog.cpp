//
// Created by Van on 2025/6/16.
//
#include "MBMS_ShowInfoDialog.h"
ShowInfoDialog::ShowInfoDialog(QWidget *parent) {
    yesButton=new QPushButton("确定");
    cancelButton=new QPushButton("关闭");
    reminder=new QLabel("reminder");
    message=new QTextEdit("message");
    message->setReadOnly(true);
    mainLayout=new QVBoxLayout(this);
    setLayout(mainLayout);
    for (auto &i:v) {
        i=new QHBoxLayout();
        mainLayout->addLayout(i);
    }
    v[0]->addWidget(reminder);
    v[0]->addWidget(message);
    v[1]->addWidget(yesButton);
    v[1]->addWidget(cancelButton);
    connect(yesButton, &QPushButton::clicked, this, &ShowInfoDialog::close);
    connect(cancelButton, &QPushButton::clicked, this, &ShowInfoDialog::close);
}
void ShowInfoDialog::setShowInfo(const std::string_view reminderStr,const std::string_view messageStr) {
    reminder->setText(reminderStr.data());
    message->setText(messageStr.data());
}

