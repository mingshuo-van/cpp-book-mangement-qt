//
// Created by Van on 2025/6/1.
//
#include "MBMS_Library.h"

#include "MBMS_AdminUser.h"

bool Library::contains(const Book &book) const {
    for (auto &i: bookList) {
        if (book == *i) {
            return true;
        }
    }
    return false;
}

bool Library::contains(const User &user) const {
    for (auto &i: userList) {
        if (user == *i) {
            return true;
        }
    }
    return false;
}

Library::Library(const string_view title): title(title) {
    pathBookList = {this->title + "bookList.txt"};
    pathUserList = {this->title + "userList.txt"};
    pathRankingList = {this->title + "rankingList.txt"};
    pathAdminList={this->title+"adminList.txt"};
    //thread loadingThread(Util::printLoading, ref(stopPrint));
    readData();
    //stopPrint = true;
    // if (loadingThread.joinable()) {
    //     loadingThread.join();
    // }
}

Library::~Library() {
    if (successfulRead && changed)
        writeData();
    for (auto &i: bookList) {
        delete i;
        i = nullptr;
    }
    for (auto &i: userList) {
        delete i;
        i = nullptr;
    }
}

Book *Library::getBook(const string_view uid) {
    for (auto &i: bookList) {
        if (uid == i->getId()) {
            return i;
        }
    }
    return &NotExistB;
}

User *Library::getUser(const string_view uid) {
    for (auto &i: userList)
        if (uid == i->getId()) {
            return i;
        }
    return &NotExistU;
}

bool Library::addBook(Book *book) {
    if (!contains(*book)) {
        bookList.emplace_back(book);
        rankingList[book->getId()];
        return true;
    }
    delete book;
    return false;
}

bool Library::addBook(Book &book) {
    return addBook(&book);
}

string Library::addUser(User *user) {
    if (!contains(*user)) {
        userList.emplace_back(user);
        return user->getName() + " (uid:" + user->getId() + ") 添加成功！" ;
    }
    string temp= user->getName() + " (uid:" + user->getId() + ") 重复添加！" ;
    delete user;
    return temp;
}

string Library::addUser(User &user) {
    return addUser(&user);
}

string Library::putUser(User &user) {
    ostringstream oss;
    oss << user.getId() << "," << user.getName();
    for (const auto &i: user.getBookList()) {
        if (i.first!=&NotExistB)
            oss << "," << i.first->getId() << "," << i.second;
    }
    oss << "\n";
    return oss.str();
}

string Library::putBook(Book &book) {
    ostringstream oss;
    oss << book.getId() << "," << book.getTitle() << "," << book.getAuthor() << "," << book.getTotalCount() << "," <<
            book.getPrice();
    for (const auto &i: book.getNameList()) {
        if (i.first!=&NotExistU)
            oss << "," << i.first->getId() << "," << i.second;
    }
    oss << "\n";
    return oss.str();
}

bool Library::writeData() {
    ofstream outputB{pathBookList};
    ofstream outputU{pathUserList};
    ofstream outputR{pathRankingList};
    ofstream outputA{pathAdminList};
    for (const auto &i: bookList) {
        outputB << putBook(*i);
    }
    outputB.close();
    for (const auto &i: userList) {
        if (dynamic_cast<AdminUser*>(i)!=nullptr)
            outputA<<putUser(*i);
        else
            outputU << putUser(*i);
    }
    outputU.close();
    for (const auto &i: rankingList) {
        if (getBook(i.first)!=&NotExistB)
            outputR << i.first << "," << i.second << "\n";
    }
    outputR.close();
    return true;
}

bool Library::readData() {
    if (!exists(pathBookList)) {
        ofstream(pathBookList).close();
    }
    if (!exists(pathUserList)) {
        ofstream(pathUserList).close();
    }
    if (!exists(pathRankingList)) {
        ofstream(pathRankingList).close();
    }
    if (!exists(pathAdminList)) {
        ofstream(pathAdminList).close();
    }
    if (file_size(pathAdminList)==0) {
        userList.push_back(new AdminUser{"U00000","Administrator"});
        changed=true;
    }
    ifstream inputB{pathBookList};
    ifstream inputU{pathUserList};
    ifstream inputR{pathRankingList};
    ifstream inputA{pathAdminList};
    if (inputB.fail() || inputU.fail() || inputR.fail()||inputA.fail()) {
        cout << "数据读入失败！" << endl;
        successfulRead = false;
        return false;
    }
    vector<vector<pair<string, long long> > > book;
    vector<vector<pair<string, long long> > > user;
    istringstream issB;
    string uid, title, author, strTC, strPr, strLL;
    int totalCount = 0;
    double price = 0;
    string line;
    long long time;
    while (getline(inputB, line)) {
        issB.clear();
        issB.str(line);
        getline(issB, uid, ',');
        getline(issB, title, ',');
        getline(issB, author, ',');
        getline(issB, strTC, ',');
        getline(issB, strPr, ',');
        totalCount = stoi(strTC);
        price = stod(strPr);
        Book *b = new Book{uid, title, author, totalCount, price};
        bookList.emplace_back(b);
        book.emplace_back();
        while (getline(issB, uid, ',') && getline(issB, strLL, ',')) {
            time = stol(strLL);
            book.back().emplace_back(uid, time);
        }
    }
    if (!inputB.eof()) {
        cout << "书籍信息读取不完整！" << endl;
        successfulRead = false;
    }
    inputB.close();
    istringstream issU;
    string name;
    while (getline(inputU, line)) {
        issU.clear();
        issU.str(line);
        getline(issU, uid, ',');
        getline(issU, name, ',');
        User *u = new User{uid, name};
        userList.emplace_back(u);
        user.emplace_back();
        while (getline(issU, uid, ',') && getline(issU, strLL, ',')) {
            time = stol(strLL);
            user.back().emplace_back(uid, time);
        }
    }
    if (!inputB.eof()) {
        cout << "用户信息读取不完整！" << endl;
        successfulRead = false;
    }
    inputU.close();
    for (int i = 0; i < book.size(); ++i) {
        for (int j = 0; j < book[i].size(); ++j) {
            User *temp = getUser(book[i][j].first);
            if (*temp != NotExistU)
                bookList[i]->getNameList().emplace_back(temp, book[i][j].second);
            bookList[i]->setBorrowedCount(bookList[i]->getBorrowedCount() + 1);
        }
    }
    for (int i = 0; i < user.size(); ++i) {
        for (int j = 0; j < user[i].size(); ++j) {
            Book *temp = getBook(user[i][j].first);
            if (*temp != NotExistB)
                userList[i]->getBookList().emplace_back(temp, user[i][j].second);
        }
    }
    istringstream issR;
    while (getline(inputR, line)) {
        issR.clear();
        issR.str(line);
        getline(issR, uid, ',');
        getline(issR, strTC);
        totalCount = stoi(strTC);
        if (*getBook(uid) != NotExistB)
            rankingList.try_emplace(uid, totalCount);
    }
    if (!inputR.eof()) {
        cout << "用户信息读取不完整！" << endl;
        successfulRead = false;
    }
    inputR.close();
    istringstream issA;
    user.clear();
    while (getline(inputA,line)) {
        issA.clear();
        issA.str(line);
        getline(issA,uid,',');
        getline(issA,name,',');
        AdminUser *admin=new AdminUser{uid,name};
        userList.push_back(admin);
        user.emplace_back();
        while (getline(issA, uid, ',') && getline(issA, strLL, ',')) {
            time = stol(strLL);
            user.back().emplace_back(uid, time);
        }
    }
    if (!inputA.eof()){
        cout << "管理员用户信息读取不完整！" << endl;
        successfulRead = false;
    }
    inputA.close();
    for (int i=0;i<user.size();++i) {
       for (int j=0;j<user[i].size();++j) {
           Book *b=getBook(user[i][j].first);
           userList[userList.size()-user.size()+i]->getBookList().emplace_back(b,user[i][j].second);
       }
    }
    return true;
}

bool Library::contains(const Book *book) const {
    return contains(*book);
}

bool Library::contains(const User *user) const {
    return contains(*user);
}

string Library::putBook(Book *book) {
    return putBook(*book);
}

string Library::putUser(User *user) {
    return putUser(*user);
}


string Library::ranking() {
    int n = 0;
    vector<pair<string, int> > v(rankingList.begin(), rankingList.end());
    auto compareByValue = [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        return a.second > b.second;
    };
    ostringstream oss;
    sort(v.begin(), v.end(), compareByValue);
    for (auto &i: v) {
        oss << "第" << ++n << "名:";
        oss<<getBook(i.first)->display();
    }
    return oss.str();
}

bool Library::deleteBook(Book *book) {
    auto it=find_if
    (bookList.begin(),bookList.end(),[book](const Book *e){return book==e;});
   if (it!=bookList.end()) {
       delete *it;
       bookList.erase(it);
       changed=true;
       return true;
   }
    return false;
}

bool Library::deleteUser(User *user) {
    auto it=find_if
    (userList.begin(),userList.end(),[user](const User *e){return *user==*e;});
    if (it!=userList.end()) {
        delete *it;
        userList.erase(it);
        changed=true;
        return true;
    }
    return false;
}

vector<Book *> &Library::getBookList() {
    return bookList;
}
const string Library::getTitle() const {
    return title;
}
const Book *Library::getNotExistBook() const {
    return &NotExistB;
}
const User *Library::getNotExistUser() const {
    return &NotExistU;
}
string Library::displayAllBook() const {
    ostringstream oss;
    if (!bookList.empty()) {
        for (auto &i:bookList) {
            oss<<i->display();
        }
    }else {
        oss<<"图书馆暂无书籍"<<endl;
    }
    return oss.str();
}

int Library::borrowBook(const string_view uidB, User *user,int k) {
    Book *book = getBook(uidB);
    bool res = false;
    if (book != &NotExistB) {
        res = user->borrowBook(book,k);
        if (res) {
            ++rankingList[uidB.data()];
            return 0;
        }
    }
    return -1;
}

string Library::regexSearchTitle(const string_view target) {
    regex pattern{target.data()};
    ostringstream oss;
    for (const auto &i:bookList) {
        if (regex_search(i->getTitle(),pattern)) {
            oss<<i->display();
        }
    }
    if (oss.tellp()==0) {
        oss<<"无符合要求书名要求的书籍!"<<endl;
    }
    return oss.str();
}
string Library::regexSearchAuthor(const string_view target) {
    regex pattern{target.data()};
    ostringstream oss;
    for (const auto &i:bookList) {
        if (regex_search(i->getAuthor(),pattern)) {
            oss<<i->display();
        }
    }
    if (oss.tellp()==0) {
        oss<<"无符合作者名要求书籍!"<<endl;
    }
    return oss.str();
}

string Library::returnBook(Book *book,User *user) {
    string res;
    if (book != &NotExistB) {
        res = user->returnBook(book);
        if (res!="书籍无外借，还书失败！") {
            if (res == "0") {
                return "还书成功，无超时罚金！" ;
            }
            return "还书成功，超时罚金:" + res+"(元)";
        }
        return res;
    }
    return "图书馆无本书信息！";
}

string Library::renew(Book *book, User *user,int k) {
    return user->renew(book,k);
}

void Library::setChanged(bool res) {
    changed=res;
}

bool Library::isChanged() {
    return changed;
}

string Library::displayAddUser() const {
    ostringstream oss;
    for (auto &i:userList) {
        oss<<i->displayFirst()<<"[\n"<<i->displaySecond()<<"]\n\n";
    }
    return oss.str();
}
