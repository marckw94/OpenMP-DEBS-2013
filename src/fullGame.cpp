//
// Created by Francesco on 27/09/2018.
//
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <vector>
#include <map>


#include "fullGame.h"
long long int firstHalf = 10753295594424116;
long long int firstHalfend = 12557295594424116;
long long int secondHalf = 14879639146403495;
std::vector<std::string> interruptionIntervalFirstHalfBegin;
std::vector<std::string> interruptionIntervalFirstHalfEnd;
std::vector<std::string> interruptionIntervalSecondHalfBegin;
std::vector<std::string> interruptionIntervalSecondHalfEnd;

/*
 * Function that preprocess the full-game.csv and divide it in smaller file, one for each player and one for the ball.
 * The datas with timestamp that are:
 *      1. before the start of the game
 *      2. in the first half pause
 *      3. after the end of the game
 *      4. in an interruption interval
 * are deleated
 *
 * path: path ot the middleware directory
 * meta: struct of the metadatas
 * interruption: class of all the interruption to manage
 *
 *
 */

void Debs::fullGame::fullGameInitialize(std::string path, Debs::metadatas meta, Debs::Interruption interruption) {
    interruptionIntervalFirstHalfBegin = interruption.getInterruptionIntervalFirstHalfBegin();
    interruptionIntervalFirstHalfEnd = interruption.getInterruptionIntervalFirstHalfEnd();
    interruptionIntervalSecondHalfBegin = interruption.getInterruptionIntervalSecondHalfBegin();
    interruptionIntervalSecondHalfEnd = interruption.getInterruptionIntervalSecondHalfEnd();

    auto referee = meta.referee;
    auto ball = meta.ball;
    auto player = meta.player;

    if(!boost::filesystem::exists(path + "/full-game")){
        std::cout << "Directory " << path + "/full-game " << "doesn't exist" <<std::endl;
        return;
    }

    std::string directoryPath = path + "/sensors";
    if(boost::filesystem::is_directory(directoryPath )){

        std::cout << "Initialization already done, skip to the analysis" << std::endl;
        return;
        }
    boost::filesystem::create_directories(directoryPath);

    std::ifstream fullGameFile (path + "/full-game/full-game.csv");
    std::map<std::string, std::ofstream*> outputFiles;

    std::string line;
    bool firstHalfStart = false;
    std::vector<int> listParamenterAlreadyTaken;
    bool firstHalfends = false;

    bool gameEnd = false;
    unsigned long long int timestamp = 0;
    long long int savedTimestampMilliseconds = 0;
    std::string destination_file = "";
    std::cout << "Search for the starting time of the game" << std::endl;
    int i = 0;
    while(std::getline(fullGameFile, line)){
        if (!firstHalfStart){
            if(i % 10000 == 0){
                std::cout << "Match not started yet " << timestamp << std::endl;
            }
            std::vector<std::string> line_split = Utils::split_string(line, ',');
            timestamp = std::stoull(line_split.at(1));
            firstHalfStart = gameIsStart(timestamp);
            ++i;
        }
        else {
            std::vector<std::string> line_split = Utils::split_string(line, ',');
            int sensor_id = std::stoi(line_split.at(0));
            timestamp = std::stoull(line_split.at(1));
            int x = std::stoi(line_split.at(2));
            int y = std::stoi(line_split.at(3));
            int z = std::stoi(line_split.at(4));

            long long int currentTimestampMilliseconds = (long long) timestamp / 1000000000;
            ++i;
            if (savedTimestampMilliseconds != currentTimestampMilliseconds){
                listParamenterAlreadyTaken.clear();
                savedTimestampMilliseconds = currentTimestampMilliseconds;
            }

            auto control = std::find(listParamenterAlreadyTaken.begin(), listParamenterAlreadyTaken.end(),sensor_id);
            if (control == std::end(listParamenterAlreadyTaken)){

                if (!firstHalfends) {

                    if(i % 1000 == 0){
                        std::cout << "First half reading is elaboration "<< timestamp-firstHalf << " "<<Utils::fromPicoToTime(timestamp) << std::endl;
                    }

                    if (!gameNotStop(timestamp, firstHalf,0)) {
                        if (ball.isSensorBall(sensor_id)) {
                            destination_file = "/ball.csv";
                        }
                        if (referee.isRefereeSensor(sensor_id)){
                            destination_file = "";
                        }

                        if (!player.isHimSensor(sensor_id).empty()){
                            destination_file ="/" + player.isHimSensor(sensor_id)+".csv";
                        }

                        if (!destination_file.empty()) {
                            if (outputFiles.find(destination_file) == outputFiles.end()) {
                                std::cout << "New file" << std::endl;

                                std::ofstream *coffstream = new std::ofstream(
                                        directoryPath + destination_file, std::ios::binary);
                                outputFiles[destination_file] = coffstream;
                            }
                            (*outputFiles[destination_file]) << currentTimestampMilliseconds << ',' << sensor_id << ',' << x << ',' << y << ','
                                                             << z << '\n';
                        }

                    }
                    else{
                        if(i % 1000 == 0){
                            std::cout << "An interruption is started at time: " << Utils::fromPicoToTime(timestamp) << std::endl;

                        }
                    }

                    if (timestamp >= firstHalfend){
                        firstHalfends = true;
                        std::cout << "First half ends" << std::endl;
                    }


                } else { //Entro se il primo tempo è finito

                    if (!gameEnd) {

                        if (i % 1000 == 0) {

                            std::cout << "Second half reading is elaboration " << timestamp-firstHalf << " "<<Utils::fromPicoToTime(timestamp) << std::endl;
                        }

                        if (!gameNotStop(timestamp, firstHalfends, 1)) {

                            if (ball.isSensorBall(sensor_id)) {
                                destination_file = "/ball.csv";
                            }

                            if (referee.isRefereeSensor(sensor_id)){
                                destination_file = "";
                            }

                            if (!player.isHimSensor(sensor_id).empty()){
                                destination_file ="/" + player.isHimSensor(sensor_id)+".csv";
                            }

                            if (!destination_file.empty()) {

                                if (outputFiles.find(destination_file) == outputFiles.end()) {

                                    std::ofstream *coffstream = new std::ofstream(
                                            directoryPath + destination_file, std::ios::binary);
                                    outputFiles[destination_file] = coffstream;
                                }

                                (*outputFiles[destination_file]) << currentTimestampMilliseconds << ',' << sensor_id << ',' << x << ',' << y << ','
                                                                 << z << '\n';
                            }
                        } else {
                            if (i % 1000 == 0) {
                                std::cout << "An interruption is started at time: " << Utils::fromPicoToTime(timestamp) << std::endl;

                            }
                        }
                        gameEnd = gameIsEnd(timestamp);
                    }else{

                        for (auto const& x : outputFiles)
                        {
                            x.second->close();
                        }
                        outputFiles.erase(outputFiles.begin(), outputFiles.end());
                        std::cout << "End of the initialization of the file" << std::endl;
                        return;
                    }
                }
            }
            listParamenterAlreadyTaken.push_back(sensor_id);
        }
    }
}

/*
 * Function that control if the timestamp in input i represent the start of the game
 *
 * i: timestamp to analyze
 *
 * return: true if game is started else false
 */

bool Debs::fullGame::gameIsStart(unsigned long long int i) {
    if (i >= firstHalf){
        return true;
    }
    return false;
}

/*
 * Function that control if the timestamp in input i represent the end of the game
 *
 * i: timestamp to analyze
 *
 * return: true if game is ended else false
 */

bool Debs::fullGame::gameIsEnd(unsigned long long int i){
    if (i >= secondHalf){
        return true;
    }
    return false;
}

/*
 * Function that control if the game is not paused in the timestamp in input
 *
 * timestamp: timestamp to analyze
 * half: timestamp of the begin of firstHalf or begin of secondHalf
 * whatHalf: 0 if the timestamp is about firstHalf else 1
 *
 * return true if there is a pause else false
 */

bool Debs::fullGame::gameNotStop(unsigned long long int timestamp, long long int half, int whatHalf) {
    std::vector<std::string> a = {};
    std::vector<std::string> b = {};
    if(whatHalf == 0){
        a = interruptionIntervalFirstHalfBegin;
        b = interruptionIntervalFirstHalfEnd;
    }else{
        a = interruptionIntervalSecondHalfBegin;
        b = interruptionIntervalSecondHalfEnd;
    }

    for (unsigned i=0; i<a.size(); i++){
        auto beginIntervalString = a.at(i);
        auto beginIntervalInt = Utils::fromTimeToPico(beginIntervalString,half);
        auto endIntervalString = b.at(i);
        auto endIntervalInt = Utils::fromTimeToPico(endIntervalString,half);
        if(timestamp >= beginIntervalInt and timestamp <= endIntervalInt){
            return true;
        }
    }

    return false;
}






