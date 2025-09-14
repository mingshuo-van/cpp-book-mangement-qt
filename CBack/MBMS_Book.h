//
// Created by Van on 2025/5/30.
//

#ifndef MBMS_BOOK_H
#define MBMS_BOOK_H
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
class User;
using namespace std;
constexpr long long DDL = 14 * 24 * 3600;

class Book {
public:
    bool operator==(const Book &book) const;

    Book(const string_view uid,
         const string_view title,
         const string_view author,
         const int totalCount,
         const double price); //构造函数
    bool lend(User &user); //借书
    bool lend(User *user); //借书
    string returnBook(User &user); //还书
    string returnBook(User *user); //还书
    bool renew(User &user,int k); //续借
    bool renew(User *user,int k); //续借
    string display(); //展示书籍信息
    bool contains(const User &user); //查询用户信息是否存在于nameList
    bool contains(const User *user); //查询用户信息是否存在于nameList
    vector<pair<User *, long long> > &getNameList();

    const string &getId() const;

    const string &getTitle() const;

    const int getTotalCount() const;

    const int getBorrowedCount() const;
    const string &getAuthor() const;

    void setBorrowedCount(int num);
    const double getPrice() const;
private:
    string uid;//书籍编号
    string title; //书名
    string author; //作者名
    int totalCount = 0; //总数
    int borrowedCount = 0; //已借出的数目
    double price = 0; //书籍的价格
    vector<pair<User *, long long> > nameList; //借阅用户向量  用户，借阅时间
};
#endif //MBMS_BOOK_H
