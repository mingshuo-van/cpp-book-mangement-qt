//
// Created by Van on 2025/6/16.
//
#include "MBMS_TempGetMessageWidget.h"

TempGetMessageWidget::TempGetMessageWidget(QWidget *parent) : SubWidget(parent) {
    connect(cancelButton, &QPushButton::clicked, this, [this] {
        close();
    });
}

void TempGetMessageWidget::setLabelOne(const string_view str) {
    label1->setText(str.data());
}

void TempGetMessageWidget::setLabelTwo(const string_view str) {
    label2->setText(str.data());
}

void TempGetMessageWidget::setTextEdit(const string_view message) {
    point = new QTextEdit();
    point->setText(message.data());
    layoutMain->addWidget(point);
    point->setReadOnly(true);
}

QPushButton *TempGetMessageWidget::getCancelButton() {
    return cancelButton;
}

QPushButton *TempGetMessageWidget::getYesButton() {
    return yesButton;
}
