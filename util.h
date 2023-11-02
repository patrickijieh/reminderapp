#ifndef UTIL_H
#define UTIL_H

#include <chrono>
#include <thread>
#include <iostream>

class util {

public:
    static void sleep(int ms);
    static std::string hash_string(std::string data);
};

#endif // UTIL_H
