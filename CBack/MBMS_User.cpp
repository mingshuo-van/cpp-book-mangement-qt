//
// Created by Van on 2025/5/30.
//
#include "MBMS_User.h"

#include <fstream>

#include "MBMS_Util.h"
#include "MBMS_Book.h"

User::User(const string_view uid, const string_view name): uid(uid), name(name) {
}

const string &User::getId() const {
    return uid;
}

const string &User::getName() const {
    return name;
}

vector<pair<Book *, long long> > &User::getBookList() {
    return bookList;
}

bool User::operator==(const User &user) const {
    if (uid == user.uid)
        return true;
    return name == user.name;
}

bool User::contains(Book &book) const {
    for (auto &i: bookList) {
        if (book == *i.first) {
            return true;
        }
    }
    return false;
}

bool User::borrowBook(Book &book,int k) {
    if (book.lend(*this)) {
        long long temp = 0;
        for (auto &i: book.getNameList()) {
            if (i.first == this) {
                temp = i.second;
            }
        }
        bookList.emplace_back(&book, temp + DDL*k);
        return true;
    }
    return false;
}

double User::getMoney(Book &book) {
    for (auto &i: bookList) {
        if (book == *i.first) {
            long long temp = Util::getTimeNow();
            if (i.second < temp) {
                return static_cast<double>(temp - i.second) / DAY * 0.5;
            }
        }
    }
    return 0;
}

string User::returnBook(Book &book) {
    double res = getMoney(book);
    string temp=book.returnBook(*this);
    if (temp.empty()) {
        string outcome=to_string(res);
        return Util::processMoney(outcome);
    }
    return temp; //还书失败
}

bool User::borrowBook(Book *book,int k) {
    return borrowBook(*book,k);
}

double User::getMoney(Book *book) {
    return getMoney(*book);
}

string User::returnBook(Book *book) {
    return returnBook(*book);
}

string User::displayFirst() {
    ostringstream oss;
    oss << "用户 " << name << " (uid:" << uid << ") 已借阅图书本数：" << bookList.size() << endl;
    return oss.str();
}

string User::displaySecond() {
    ostringstream oss;
    if (!bookList.empty())
        for (auto &i: bookList) {
            oss<<i.first->display();
        }
    else
        oss<<"暂无借阅书籍"<<endl;
    return oss.str();
}

string User::renew(Book &book,int k) {
    if (book.renew(this,k)) {
        return book.getTitle() +" (uid:" +book.getId() + ") 续借成功" ;
    }
    return "续借失败!";
}

string User::renew(Book *book,int k) {
    return renew(*book,k);
}
