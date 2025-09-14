//
// Created by Van on 2025/6/16.
//

#ifndef MBMS_SHOWINFODIALOG_H
#define MBMS_SHOWINFODIALOG_H
#include <QDialog>
#include <QPushButton>
#include <string>
#include <QTextEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <vector>
#include "../CBack/MBMS_Global.h"
class ShowInfoDialog:public QDialog {
public:
    ShowInfoDialog(QWidget *parent=nullptr);
    void setShowInfo(const std::string_view reminder,const std::string_view message);
private:
    QPushButton *yesButton;
    QPushButton *cancelButton;
    QLabel *reminder;
    QTextEdit *message;
    std::vector<QHBoxLayout*> v{2};
    QVBoxLayout *mainLayout;
};
#endif //MBMS_SHOWINFODIALOG_H
