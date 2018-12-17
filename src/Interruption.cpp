//
// Created by Francesco on 20/09/2018.
//
#include <iostream>
#include <fstream>
#include "Interruption.h"
#include <boost/filesystem.hpp>
#include <vector>

/*
 * Getter of interruptionIntervalFirstHalfBegin
 */

std::vector<std::string> Debs::Interruption::getInterruptionIntervalFirstHalfBegin() {
    return this->interruptionIntervalFirstHalfBegin;
}

/*
 * Getter of interruptionIntervalFirstHalfEnd
 */

std::vector<std::string> Debs::Interruption::getInterruptionIntervalFirstHalfEnd() {
    return this->interruptionIntervalFirstHalfEnd;
}

/*
 * Getter of interruptionIntervalSecondHalfBegin
 */

std::vector<std::string> Debs::Interruption::getInterruptionIntervalSecondHalfBegin() {
    return this->interruptionIntervalSecondHalfBegin;
}

/*
 * Getter of interruptionIntervalSecondHalfEnd
 */

std::vector<std::string> Debs::Interruption::getInterruptionIntervalSecondHalfEnd() {
    return this->interruptionIntervalSecondHalfEnd;
}

/*
 * Function that load the interruption interval from the datapath given in input
 *
 * datPath: datapath of the middleware directory
 */

void Debs::Interruption::addInterruptionInterval(std::string dataPath) {

    if (!boost::filesystem::exists(dataPath)) {

        std::cout << "something Wrong, the datapath doesn't exist" << std::endl;
        return;

    }
    std::string dataPathFirstHalf;
    dataPathFirstHalf = dataPath + "/referee-events/referee-events/Game_Interruption/FirstHalf.csv";
    if (!boost::filesystem::exists(dataPathFirstHalf)){

        std::cout << "something Wrong, the datapath of first half interruption's doesn't exist" << std::endl;
        return;

    }
    std::ifstream file (dataPathFirstHalf);
    std::string value;
    std::vector<std::string> adding = {};
    int i = 1;
    int column = 5;
    if (file.is_open()) {

        while (file.good()) {

            getline(file, value, ';');
            if(i % column == 3){

                adding.push_back(value);
            }

            if (adding.size() == 2){

                this->interruptionIntervalFirstHalfBegin.push_back(adding[0]);
                this->interruptionIntervalFirstHalfEnd.push_back(adding[1]);
                std::cout<< "Added " << adding[0]<<"  "<< adding[1] << std::endl;
                adding.clear();
            }
            if(i % column == 0){++i;}
            ++i;
        }
    }
    std::cout << "Adding all the first Half interruption interval to the data structure " << std::endl;
    std::string dataPathSecondHalf;
    dataPathSecondHalf = dataPath + "/referee-events/referee-events/Game_Interruption/SecondHalf.csv";
    if (!boost::filesystem::exists(dataPathSecondHalf)){

        std::cout << "something Wrong, the datapath of second half interruption's doesn't exist" << std::endl;
        return;
    }
    std::ifstream file2 (dataPathSecondHalf);
    i = 1;
    column = 5;
    if (file2.is_open()) {

        while (file2.good()) {

            getline(file2, value, ';');
            if(i % column == 3){
                adding.push_back(value);
            }
            if (adding.size() == 2){

                this->interruptionIntervalSecondHalfBegin.push_back(adding[0]);
                this->interruptionIntervalSecondHalfEnd.push_back(adding[1]);
                std::cout<< "Added " << adding[0]<<"  "<< adding[1] << std::endl;
                adding.clear();
            }
            if(i % column == 0){++i;}
            ++i;
        }
    }
    std::cout << "Adding all the second Half interruption interval to the data structure " << std::endl;
    file.close();
    file2.close();
    std::cout << "Adding all the interruption " << std::endl;
}