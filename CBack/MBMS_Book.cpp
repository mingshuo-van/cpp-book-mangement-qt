//
// Created by Van on 2025/5/30.
//
#include "MBMS_Book.h"
#include "MBMS_Util.h"
#include "MBMS_User.h"

Book::Book(const string_view uid,
           const string_view title,
           const string_view author,
           const int totalCount,
           const double price): uid(uid), title(title), author(author), totalCount(totalCount), price(price) {
}

const string &Book::getId() const {
    return uid;
}

const string &Book::getTitle() const {
    return title;
}

const int Book::getBorrowedCount() const {
    return borrowedCount;
}

const int Book::getTotalCount() const {
    return totalCount;
}

bool Book::contains(const User &user) {
    for (auto &i: nameList) {
        if (*i.first == user) {
            return true;
        }
    }
    return false;
}


bool Book::lend(User &user) {
    if (!contains(user)) {
        if (borrowedCount < totalCount) {
            ++borrowedCount;
            nameList.emplace_back(&user, Util::getTimeNow());
            return true;
        }
    }
    return false;
}

string Book::returnBook(User &user) {
    if (borrowedCount == 0 || !contains(user)) {
        return "书籍无外借，还书失败！";
    }
    --borrowedCount;
    auto it1 = find_if(nameList.begin(), nameList.end(), [&user](const auto &element) {
        return *element.first == user;
    });
    if (it1 != nameList.end()) {
        nameList.erase(it1);
    }
    auto it2 = find_if(user.getBookList().begin(), user.getBookList().end(), [this](const auto &element) {
        return element.first == this;
    });
    if (it2 != user.getBookList().end()) {
        user.getBookList().erase(it2);
    }
    return "";
}

bool Book::operator==(const Book &book) const {
    if (uid == book.uid)
        return true;
    return title == book.title && author == book.author && price == book.price;
}

string Book::display() {
    ostringstream oss;
    oss << "书籍《" << title << "》 (uid:" << uid << ") 作者：" << author << " 总数：" << totalCount << " 已借出：" << borrowedCount
            <<
            endl;
    return oss.str();
}

bool Book::renew(User &user,int k) {
    for (auto &i: user.getBookList()) {
        if (i.first == this) {
            i.second += DDL*k;
            return true;
        }
    }
    return false;
}

vector<pair<User *, long long> > &Book::getNameList() {
    return nameList;
}

const string &Book::getAuthor() const {
    return author;
}

void Book::setBorrowedCount(int num) {
    borrowedCount = num >= 0 ? num : 0;
}

const double Book::getPrice() const {
    return price;
}

bool Book::contains(const User *user) {
    return contains(*user);
}

bool Book::lend(User *user) {
    return lend(*user);
}

bool Book::renew(User *user,int k) {
    return renew(*user,k);
}

string Book::returnBook(User *user) {
    return returnBook(*user);
}
