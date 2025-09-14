//
// Created by Van on 2025/6/19.
//
#include "MBMS_checkBook.h"

CheckBook::CheckBook(QWidget *parent): TempGetMessageWidget(parent) {
    for (int i = 0; i < 3; ++i) {
        label[i] = new QLabel();
        line[i] = new QLineEdit();
        layout[i] = new QHBoxLayout();
        layout[i]->addWidget(label[i]);
        layout[i]->addWidget(line[i]);
        layoutMain->addLayout(layout[i]);
    }
    if (buttonLayout) {
        layoutMain->removeItem(buttonLayout);
    }
    layoutMain->addLayout(buttonLayout);
    label1->setText("uid:");
    label2->setText("name:");
    label[0]->setText("author:");
    label[1]->setText("totalCount:");
    label[2]->setText("price:");
    yesButton->setText("确定:");
    cancelButton->setText("取消:");
}

int CheckBook::getTotalCount() {
    return stoi(line[1]->text().toStdString());
}

string CheckBook::getAuthor() {
    return line[0]->text().toStdString();
}

double CheckBook::getPrice() {
    return stod(line[2]->text().toStdString());
}
