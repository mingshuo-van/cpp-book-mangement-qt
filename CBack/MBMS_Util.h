//
// Created by Van on 2025/5/31.
//

#ifndef MBMS_UTIL_H
#define MBMS_UTIL_H
#include <chrono>
#include <filesystem>
#include <string>
#include <atomic>
#include <thread>
#include <iostream>
using namespace std;
namespace fs = filesystem;

class Util {
public:
    static long long getTimeNow() {
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).
                count();
    }

    static void printLoading(atomic<bool> &stopPrint) {
        cout << "正在加载中……" << endl;
        while (!stopPrint) {
            int num = 15;
            for (int i = 0; i < num; ++i) {
                cout << "- " << flush;
                this_thread::sleep_for(chrono::milliseconds(30));
            }
            cout << "\r" << string(50, ' ') << "\r";
        }
        cout << "加载结束！" << endl << endl;
    }
    static string processMoney(string &outcome) {
        const char* s=outcome.c_str();
        for (const char *it = outcome.c_str() + outcome.length()-1; it>=s; --it) {
            if (*it == '0') {
                outcome.pop_back();
            } else {
                if (*it == '.') {
                    outcome.pop_back();
                }
                break;
            }
        }
        size_t index = outcome.find('.');
        if (index == string::npos) {
            return outcome;
        }
        if (index + 3 <= outcome.size()) {
            return outcome.substr(0, index + 3);
        }
        return outcome;
    }
};

#endif //MBMS_UTIL_H
