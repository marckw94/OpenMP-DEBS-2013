//
// Created by Francesco on 20/09/2018.
//
#include <iostream>

#ifndef MIDDLEWARE_UTILS_H
#define MIDDLEWARE_UTILS_H

class Utils {
public:
    static std::string fromPicoToTime(long long picoseconds);

    static std::vector<std::string> split_string(const std::string &s, const char &separator);

    static long long int fromTimeToPico(std::string time, long long int startTime);

    static std::string fromMilliToTime(long long milliseconds);

    static std::string fromSecondToTime(long int seconds);
};


#endif //MIDDLEWARE_UTILS_H
