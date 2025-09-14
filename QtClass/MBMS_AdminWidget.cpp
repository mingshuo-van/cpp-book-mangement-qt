//
// Created by Van on 2025/6/18.
//
#include "MBMS_AdminWidget.h"

#include <QMessageBox>

#include "MBMS_checkBook.h"
#include "MBMS_ShowInfoDialog.h"
#include "MBMS_TempGetMessageWidget.h"

AdminWidget::AdminWidget(QWidget *parent): CommonUserWidget(parent) {
    attachedLayout = new QHBoxLayout();
    for (auto &i: v) {
        i = new QPushButton(this);
        i->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        attachedLayout->addWidget(i);
    }
    v[0]->setText("添加用户");
    v[1]->setText("删除用户");
    v[2]->setText("添加书籍");
    v[3]->setText("删除书籍");
    v[4]->setText("用户列表");
    mainLayout->addLayout(attachedLayout);
    connect(v[0], &QPushButton::clicked, this, [this] {
        TempGetMessageWidget *w = new TempGetMessageWidget(this);
        w->setWindowTitle("添加普通用户或管理员");
        w->setLabelOne("uid:");
        w->setLabelTwo("name");
        w->setTextEdit("如果需要退出，请点击右上角X键退出。");
        w->getYesButton()->setText("添加普通用户");
        w->getCancelButton()->setText("添加管理用户");
        w->show();
        globalLibrary->setChanged(true);
        connect(w->getYesButton(), &QPushButton::clicked, this, [this,w] {
            User *u = new User{w->getLineOne(), w->getLineTwo()};
            QMessageBox::information(this, "提醒", globalLibrary->addUser(u).data());
            w->close();
        });
        connect(w->getCancelButton(), &QPushButton::clicked, this, [this,w] {
            AdminUser *u = new AdminUser{w->getLineOne(), w->getLineTwo()};
            QMessageBox::information(this, "提醒", globalLibrary->addUser(u).data());
            w->close();
        });
    });
    connect(v[1], &QPushButton::clicked, this, [this] {
        TempGetMessageWidget *w = new TempGetMessageWidget(this);
        w->setWindowTitle("删除普通用户或管理员");
        w->setLabelOne("uid:");
        w->setLabelTwo("name");
        w->getYesButton()->setText("确定");
        w->getCancelButton()->setText("取消");
        w->show();
        globalLibrary->setChanged(true);
        connect(w->getYesButton(), &QPushButton::clicked, this, [this,w] {
            User *u = new User{w->getLineOne(), w->getLineTwo()};
            ostringstream oss;
                oss << "用户 " << u->getName() << " (uid:" << u->getId() << ") " << (globalLibrary->deleteUser(u)
                        ? "删除成功"
                        : "删除失败");
            QMessageBox::information(this, "提醒", oss.str().data());
            w->close();
        });
    });
    connect(v[2], &QPushButton::clicked, this, [this] {
        CheckBook *w = new CheckBook(this);
        w->setWindowTitle("添加书籍");
        w->show();
        globalLibrary->setChanged(true);
        connect(w->getYesButton(), &QPushButton::clicked, this, [this,w] {
            try {
                Book *b = new Book{w->getLineOne(), w->getLineTwo(), w->getAuthor(), w->getTotalCount(), w->getPrice()};
                ostringstream oss;
                oss << "《" << b->getTitle() << "》 (uid:" << b->getId() << ") " << (globalLibrary->addBook(b)
                        ? "添加成功"
                        : "添加失败");
                QMessageBox::information(this, "提醒", oss.str().data());
            } catch (const exception &e) {
                ostringstream oss;
                oss << "请输入正确的数据！" << e.what();
                QMessageBox::information(this, "警告", oss.str().data());
            }
            w->close();
        });
    });
    connect(v[3], &QPushButton::clicked, this, [this] {
        CheckBook *w = new CheckBook(this);
        w->setWindowTitle("删除书籍");
        w->show();
        globalLibrary->setChanged(true);
        connect(w->getYesButton(), &QPushButton::clicked, this, [this,w] {
            try {
                Book *b = new Book{w->getLineOne(), w->getLineTwo(), w->getAuthor(), w->getTotalCount(), w->getPrice()};
                ostringstream oss;
                oss << "《" << b->getTitle() << "》 (uid:" << b->getId() << ") " << (globalLibrary->deleteBook(b)
                        ? "删除成功"
                        : "删除失败");
                QMessageBox::information(this, "提醒", oss.str().data());
            } catch (const exception &e) {
                ostringstream oss;
                oss << "请输入正确的数据！" << e.what();
                QMessageBox::information(this, "警告", oss.str().data());
            }
            w->close();
        });
    });
    connect(v[4], &QPushButton::clicked, this, [this] {
        ShowInfoDialog *d = new ShowInfoDialog(this);
        d->setMinimumSize(300,1000);
        d->setWindowTitle("用户列表");
        d->setShowInfo("用户列表:", globalLibrary->displayAddUser());
        d->show();
    });
}
