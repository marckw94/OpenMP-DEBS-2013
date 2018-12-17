//
// Created by Francesco on 20/09/2018.
//
#include <boost/filesystem.hpp>
#include <iostream>
#ifndef MIDDLEWARE_INTERRUPTION_H
#define MIDDLEWARE_INTERRUPTION_H

namespace Debs {
    class Interruption {
    private :
        std::vector<std::string> interruptionIntervalFirstHalfBegin;
        std::vector<std::string> interruptionIntervalFirstHalfEnd;
        std::vector<std::string> interruptionIntervalSecondHalfBegin;
        std::vector<std::string> interruptionIntervalSecondHalfEnd;



    public :
        std::vector<std::string> getInterruptionIntervalFirstHalfBegin();
        std::vector<std::string> getInterruptionIntervalFirstHalfEnd();
        std::vector<std::string> getInterruptionIntervalSecondHalfBegin();
        std::vector<std::string> getInterruptionIntervalSecondHalfEnd();

        void addInterruptionInterval(std::string dataPath);


    };
}

#endif //MIDDLEWARE_INTERRUPTION_H
