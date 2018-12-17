//
// Created by Francesco on 20/09/2018.
//
#include <sstream>
#include <ctgmath>
#include <vector>
#include "Utils.h"

/* Function that translate a string in time format in picoseconds
 *
 * time: string rappresent the time
 * startTime: start of the game
 *
 * return: picosecond of the time in input
 */

long long int Utils::fromTimeToPico(std::string time, long long int startTime) {

    auto line = Utils::split_string(time,':');
    int hours = std::stoi(line[0]);
    int minutes = std::stoi(line[1]);
    auto stringOfSeconds = Utils::split_string(line[2], '.');
    int seconds = std::stoi(stringOfSeconds[0]);
    int milliseconds = std::stoi(stringOfSeconds[1]);

    minutes = hours*60 + minutes;
    seconds = minutes*60 + seconds;
    milliseconds = seconds * 1000 + milliseconds;
    long long int picoseconds = milliseconds * pow(10,9);
    return picoseconds+startTime;
}

/*
 * Function that translate a long long in a string in time format
 *
 * picoseconds: integer in picoseconds
 *
 * return: string of the time relative of the picosecond in input
 */

std::string Utils::fromPicoToTime(long long picoseconds) {
    long long startTime = 10753295594424116;
    long long rightTime = picoseconds - startTime;
    double totSecondsDouble;
    totSecondsDouble =  rightTime*pow(10,-12);
    auto totSeconds = (long) totSecondsDouble;
    auto seconds = totSeconds % 60;
    auto futureMinute = totSeconds/60;
    auto minute = futureMinute % 60;
    auto hour = futureMinute / 60;
    std::stringstream ss;
    ss << hour << ":" << minute << ":" << seconds;
    return ss.str();
}

/*
 * function that translate a long long that represent the millisecond in a string representing the time
 *
 * milliseconds: long long int representing the milliseconds
 *
 * return: string in time format for the relative millisecond given in input
 *
 */

std::string Utils::fromMilliToTime(long long milliseconds) {
    auto milli = milliseconds % 1000;
    std::stringstream milliStream;
    bool controlZero = false;
    if (milli == 0){
        milliStream << 0 << 0 << milli;
        controlZero = true;
    }if (!controlZero) {
        if (milli < 10) {
            milliStream << 0 << 0 << milli;
        }
        if (milli < 100 and milli >= 10) {
            milliStream << 0 << milli;
        } else {
            milliStream << milli;
        }
    }
    std::string milliString = milliStream.str();
    double totSecondsDouble = milliseconds*pow(10,-3);
    auto totSeconds = (long) totSecondsDouble;
    auto seconds = totSeconds % 60;
    auto futureMinute = totSeconds/60;
    auto minute = futureMinute % 60;
    std::stringstream minuteStream;
    if (minute < 10){
        minuteStream << 0 << minute;
    }
    else{
        minuteStream << minute;
    }
    std::string minuteString = minuteStream.str();
    std::stringstream secondStream;
    if (seconds < 10){
        secondStream << 0 << seconds;
    }else{
        secondStream << seconds;
    }
    std::string secondString = secondStream.str();
    std::stringstream ss;
    ss << minuteString << ":" << secondString << "." << milliString;
    return ss.str();
}

/*
 * function that translate a long that represent the second in a string representing the time
 *
 * milliseconds: long int representing the seconds
 *
 * return: string in time format for the relative second given in input
 *
 */

std::string Utils::fromSecondToTime(long totSeconds){
    auto seconds = totSeconds % 60;
    std::stringstream secondStream;
    if (seconds < 10){
        secondStream << 0 << seconds;
    }else{
        secondStream << seconds;
    }
    std::string secondString = secondStream.str();
    auto futureMinute = totSeconds/60;
    auto minute = futureMinute % 60;
    std::stringstream minuteStream;
    if (minute < 10){
        minuteStream << 0 << minute;
    }else{
        minuteStream << minute;
    }
    std::string minuteString = minuteStream.str();
    auto hour = futureMinute / 60;
    std::stringstream hourStream;
    if (hour < 10){
        hourStream << 0 << hour;
    }else{
        hourStream << hour;
    }
    std::string hourString = hourStream.str();
    std::stringstream ss;
    ss << hourString << ":" << minuteString << ":" << secondString;
    return ss.str();

}

/*
 * Function that split a string of the csv in a vector of string
 *
 * s: string to split
 * separator: separator of the string s
 *
 * return: vector of separeted strings
 */

std::vector<std::string> Utils::split_string(const std::string &s, const char &separator) {
    std::vector<std::string> result;

    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, separator)) {
        result.push_back(item);
    }

    return result;
}


