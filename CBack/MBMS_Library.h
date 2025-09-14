//
// Created by Van on 2025/6/1.
//

#ifndef MBMS_LIBRARY_H
#define MBMS_LIBRARY_H
#include "MBMS_Util.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include "MBMS_Book.h"
#include "MBMS_User.h"
#include <atomic>
#include <thread>
#include "MBMS_AdminUser.h"
#include <regex>
class Book;
class User;
using namespace std;
namespace fs = filesystem;
class Library {
public:
    Library() = default;
    Library(const string_view title);
    bool addBook(Book& book);
    bool addBook(Book* book);
    string addUser(User& user);
    string addUser(User* user);
    bool contains(const Book& book) const;
    bool contains(const Book* book) const;
    bool contains(const User& user) const;
    bool contains(const User* user) const;
    bool readData();
    bool writeData();
    vector<Book*> &getBookList();
    User* getUser(const string_view uid);
    Book* getBook(const string_view uid);
    string ranking();
    bool deleteBook(Book *book);
    bool deleteUser(User *user);
    string putBook(Book& book);
    string putBook(Book* book);
    string putUser(User& user);
    string putUser(User* user);
    const string getTitle()const;
    ~Library();
    const Book * getNotExistBook()const ;
    const User * getNotExistUser()const ;
    string displayAllBook() const;
    int borrowBook(const string_view uidB, User *user,int k);
    string regexSearchTitle(const string_view target);
    string regexSearchAuthor(const string_view target);
    string returnBook(Book *book,User *user);
    string renew(Book *book,User *user,int k);
    void setChanged(bool res);
    bool isChanged();
    string displayAddUser() const;
private:
    string title;
    vector<Book*> bookList;
    vector<User*> userList;
    Book NotExistB{"本书不存在","本书不存在","本书不存在",0,0};
    User NotExistU{"该用户不存在","该用户不存在"};
    fs::path pathBookList;
    fs::path pathUserList;
    fs::path pathRankingList;
    fs::path pathAdminList;
    bool successfulRead=true;
    bool changed=false;
    //atomic<bool> stopPrint=false;
    map<string,int> rankingList;//用于书籍借阅次数的排名
};
#endif //MBMS_LIBRARY_H
