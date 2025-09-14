//
// Created by Van on 2025/5/30.
//

#ifndef MBMS_USER_H
#define MBMS_USER_H
#include <vector>
#include <string>
#include <iostream>
class Book;
using namespace std;
constexpr long long DAY = 24 * 3600;

class User {
public:
    bool operator==(const User &user) const;

    User(const string_view uid,
         const string_view name);

    const string &getId() const;

    const string &getName() const;

    vector<pair<Book *, long long> > &getBookList();

    bool contains(Book &book) const; //查询书籍信息是否在bookList
    bool borrowBook(Book &book,int k);
    bool borrowBook(Book *book,int k);
    string returnBook(Book &book);
    string returnBook(Book *book);

    double getMoney(Book &book);
    double getMoney(Book *book);

    virtual string displayFirst();
    virtual string displaySecond();

    string renew(Book &book,int k);
    string renew(Book *book,int k);

    virtual ~User() =default;
protected:
    string uid;
    string name;
    vector<pair<Book *, long long> > bookList; //书籍信息，到期时间
};
#endif //MBMS_USER_H
