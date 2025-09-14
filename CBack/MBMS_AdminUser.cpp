//
// Created by Van on 2025/6/7.
//

#include "MBMS_AdminUser.h"

string AdminUser::displayFirst() {
    ostringstream oss;
    oss << "管理员 " << name << " (uid:" << uid << ") 已借阅图书本数：" << bookList.size() << endl;
    return oss.str();
}

string AdminUser::displaySecond() {
    ostringstream oss;
    if (!bookList.empty())
        for (auto &i: bookList) {
            oss<<i.first->display();
        }
    else
        oss<<"暂无借阅书籍"<<endl;
    return oss.str();
}
AdminUser::AdminUser(const string_view uid, const string_view name): User(uid, name) {
}

