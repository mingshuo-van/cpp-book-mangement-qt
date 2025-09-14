//
// Created by Van on 2025/6/14.
//
#include "MBMS_SubWidget.h"
SubWidget::SubWidget(QWidget *parent){
    setMinimumSize(400,300);
    label1=new QLabel("temp");
    line1=new QLineEdit();
    label2=new QLabel("temp");
    line2=new QLineEdit();
    setWindowTitle("title");
    layoutMain=new QVBoxLayout(this);
    layoutUid=new QHBoxLayout();
    layoutUid->addWidget(label1);
    layoutUid->addWidget(line1);
    layoutName=new QHBoxLayout();
    layoutName->addWidget(label2);
    layoutName->addWidget(line2);
    buttonLayout=new QHBoxLayout();
    yesButton=new QPushButton("temp");
    cancelButton=new QPushButton("temp");
    buttonLayout->addWidget(yesButton);
    buttonLayout->addWidget(cancelButton);
    layoutMain->addLayout(layoutUid);
    layoutMain->addLayout(layoutName);
    layoutMain->addLayout(buttonLayout);
    setLayout(layoutMain);
}

SubWidget::~SubWidget()=default;

string SubWidget::getLineOne() {
    return line1->text().toStdString();
}
string SubWidget::getLineTwo() {
    return line2->text().toStdString();
}
void SubWidget::deleteTwoLabel() {
    int index=layoutMain->indexOf(layoutName);
    if (index!=-1) {
        QLayoutItem *item=layoutMain->itemAt(index);
        layoutMain->removeItem(item);
        delete item->layout();
    }
}
