//
// Created by Van on 2025/6/7.
//

#ifndef MBMS_ADMINUSER_H
#define MBMS_ADMINUSER_H
#include "MBMS_User.h"
#include "MBMS_Book.h"

class AdminUser : public User {
public:
    AdminUser(const string_view uid, const string_view name);

    string displayFirst() override;
    string displaySecond() override;

};
#endif //MBMS_ADMINUSER_H
