//
// Created by Van on 2025/6/15.
//
#include "MBMS_CommonUserWidget.h"

#include <QMessageBox>

#include "MBMS_ShowInfoDialog.h"
#include "MBMS_TempGetMessageWidget.h"
#include "../CBack/MBMS_Library.h"

CommonUserWidget::CommonUserWidget(QWidget *parent) {
    setWindowTitle("用户操作界面");
    setMinimumSize(1000, 800);
    for (auto &i: v) {
        i = new QPushButton();
        i->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
    leftLayout = new QVBoxLayout();
    v[0]->setText("用户信息");
    v[1]->setText("书籍列表");
    v[2]->setText("借阅书籍");
    v[6]->setText("编号搜索");
    leftLayout->addWidget(v[0]);
    leftLayout->addWidget(v[1]);
    leftLayout->addWidget(v[2]);
    leftLayout->addWidget(v[6]);
    rightLayout = new QVBoxLayout();
    v[3]->setText("归还书籍");
    v[4]->setText("续借书籍");
    v[5]->setText("借阅排名");
    v[7]->setText("退出登录");
    rightLayout->addWidget(v[3]);
    rightLayout->addWidget(v[4]);
    rightLayout->addWidget(v[5]);
    rightLayout->addWidget(v[7]);
    mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);
    connect(v[0], &QPushButton::clicked, this, [this] {
        ShowInfoDialog *infoDialog = new ShowInfoDialog(this);
        infoDialog->setWindowTitle("用户信息");
        infoDialog->setShowInfo(globalUser->displayFirst(),
                                globalUser->displaySecond());
        infoDialog->show();
    });
    connect(v[1], &QPushButton::clicked, this, [this] {
        ShowInfoDialog *infoDialog = new ShowInfoDialog(this);
        infoDialog->setWindowTitle("书籍列表");
        string temp = "当前书籍总数:" + to_string(globalLibrary->getBookList().size());
        infoDialog->setShowInfo(temp, globalLibrary->displayAllBook());
        infoDialog->show();
    });
    connect(v[2], &QPushButton::clicked, this, [this] {
        TempGetMessageWidget *w = new TempGetMessageWidget(this);
        w->setWindowTitle("借阅书籍");
        w->setLabelOne("书籍uid:");
        w->setLabelTwo("借阅系数:");
        string m = "总申请借阅时间是由14*借阅系数(单位：天)得到的";
        w->setTextEdit(m);
        w->getYesButton()->setText("确定");
        w->getCancelButton()->setText("取消");
        w->show();
        connect(w->getYesButton(), &QPushButton::clicked, this, [this, w] {
            int res = -1;
            try {
                res = globalLibrary->borrowBook(w->getLineOne(), globalUser, stoi(w->getLineTwo()));
            } catch (const exception &e) {
                    ostringstream oss;
                    oss<<"请输入正确的数据！"<<e.what();
                    QMessageBox::information(this, "警告", oss.str().data());
                }
            ostringstream oss;
            if (res == 0) {
                oss << globalUserName << "(uid:" << globalUserUid << ") 借阅《"
                        << globalLibrary->getBook(w->getLineOne())->getTitle() << "》(uid:" << w->getLineOne()
                        << ") " << "成功！" <<
                        endl;
            } else {
                oss << globalUserName << "(uid:" << globalUserUid << ") 借阅 uid 为" << w->getLineOne()
                        << "的书 " << "失败！" << endl <<
                        "请检查信息是否正确！" << endl;
            }
            QMessageBox::information(this, "提醒", oss.str().data());
            globalLibrary->setChanged(true);
            w->close();
        });
    });
    connect(v[6], &QPushButton::clicked, this, [this] {
        TempGetMessageWidget *w = new TempGetMessageWidget(this);
        w->setWindowTitle("编号搜索");
        w->setLabelOne("书籍名称:");
        w->setLabelTwo("作者姓名:");
        string temp = "可以少字，也不要多字";
        w->setTextEdit(temp);
        w->getYesButton()->setText("确定");
        w->getCancelButton()->setText("取消");
        w->show();
        connect(w->getYesButton(), &QPushButton::clicked, this, [this,w] {
            string target = w->getLineOne();
            string name = w->getLineTwo();
            if (!target.empty() && !name.empty()) {
                ShowInfoDialog *d = new ShowInfoDialog(this);
                ostringstream oss;
                oss << "名字中有 " << target << " 或者 作者名字中有 " << name << " 的书有：";
                d->setShowInfo(oss.str(), globalLibrary->regexSearchTitle(target)
                                          + globalLibrary->regexSearchAuthor(name));
                d->show();
            } else if (!target.empty()) {
                ShowInfoDialog *d = new ShowInfoDialog(this);
                ostringstream oss;
                oss << "名字中有 " << target << " 的书有：";
                d->setShowInfo(oss.str(), globalLibrary->regexSearchTitle(target));
                d->show();
            } else if (!name.empty()) {
                ShowInfoDialog *d = new ShowInfoDialog(this);
                ostringstream oss;
                oss << "作者名字中有 " << name << " 的书有：";
                d->setShowInfo(oss.str(), globalLibrary->regexSearchAuthor(name));
                d->show();
            } else {
                QMessageBox::information(this, "警告", "书籍名和作者姓名不能都为空！");
                w->close();
            }
            globalLibrary->setChanged(true);
        });
    });
    connect(v[3], &QPushButton::clicked, this, [this] {
        TempGetMessageWidget *w = new TempGetMessageWidget(this);
        w->setWindowTitle("归还书籍");
        w->setTextEdit("当前借阅书籍:\n" + globalUser->displaySecond());
        w->setLabelOne("uid:");
        w->setLabelTwo("书籍名称:");
        w->getYesButton()->setText("确定");
        w->getCancelButton()->setText("取消");
        w->show();
        connect(w->getYesButton(), &QPushButton::clicked, this, [this,w] {
            Book *book = globalLibrary->getBook(w->getLineOne());
            if (book->getTitle() != w->getLineTwo()) {
                QMessageBox::information(this, "警告", "请检查书籍信息是否正确");
            } else {
                QMessageBox::information(this, "提醒", globalLibrary->returnBook(book, globalUser).data());
            }
            w->close();
            globalLibrary->setChanged(true);
        });
    });
    connect(v[4], &QPushButton::clicked, this, [this] {
        TempGetMessageWidget *w = new TempGetMessageWidget(this);
        w->setWindowTitle("续借书籍");
        ostringstream oss;
        oss << "总申请续借时间是由14*借阅系数(单位：天)得到的\n" << "当前借阅书籍:\n" << globalUser->displaySecond();
        w->setTextEdit(oss.str());
        w->setLabelOne("uid:");
        w->setLabelTwo("续借系数:");
        w->getYesButton()->setText("确定");
        w->getCancelButton()->setText("取消");
        w->show();
        connect(w->getYesButton(), &QPushButton::clicked, this, [this,w] {
            Book *book = globalLibrary->getBook(w->getLineOne());
            if (book != globalLibrary->getNotExistBook())
                try {
                    QMessageBox::information(this, "提醒",
                                             globalLibrary->renew(book, globalUser, stoi(w->getLineTwo())).data());
                } catch (const exception &e) {
                    ostringstream oss;
                    oss<<"请输入正确的数据！"<<e.what();
                    QMessageBox::information(this, "警告", oss.str().data());
                }
            else
                QMessageBox::information(this, "警告", "请检查书籍信息是否正确");
            w->close();
            globalLibrary->setChanged(true);
        });
    });
    connect(v[5], &QPushButton::clicked, this, [this] {
        ShowInfoDialog *d = new ShowInfoDialog(this);
        d->setWindowTitle("借阅排名");
        d->setShowInfo("借阅次数排名:", globalLibrary->ranking());
        d->show();
    });
    connect(v[7], &QPushButton::clicked, this, [this] {
        emit backLogin();
        globalLibrary->writeData();
        globalLibrary->setChanged(false);
        close();
    });
}

void CommonUserWidget::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认关闭", "你确定要关闭窗口吗？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if (globalLibrary->isChanged())
            globalLibrary->writeData();
        globalLibrary->setChanged(false);
        event->accept();
    } else {
        event->ignore();
    }
}
