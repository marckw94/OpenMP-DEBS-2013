//
// Created by Francesco on 15/11/2018.
//
#include <vector>
#include "Ball.h"

/*
 * Constuctor of the Ball
 */

Debs::Ball::Ball(std::string path) {
    this->sensorFile = new std::ifstream(path+ "/sensors/ball.csv");
}

/*
 * Getter of sensorFile
 */

std::ifstream& Debs::Ball::getSensorFile() {

    return *this->sensorFile;
}

/*
 * Getter of chunkOfPositions
 */

std::vector<Debs::Position> Debs::Ball::getChunkOfPositions() {
    return  this->chunkOfPositions;
}

/*
 * Function that add the position in input to the ball chunkOfPositions
 *
 * position: Position to add
 */

void Debs::Ball::addPositionData(Debs::Position position){
    this->chunkOfPositions.push_back(position);
}

/*
 * Function that charge the chunk of the ball with 1 second of datas takes from the file of the ball
 *
 * beginOfInterval: first timestamp to analyze
 *
 * return timestamp of the last usefull timestamp to analyze, if the file of the ball ends return 14900000
 */

long long int Debs::Ball::chargeChunk(long long int beginOfInterval) {
    this->chunkOfPositions.clear();
    bool saveFirstTimestamp = true;
    std::string line;
    long long int timestamp;
    long long int chunkSize=1000;
    while(std::getline(this->getSensorFile(), line)){
            std::vector<std::string> line_split = Utils::split_string(line, ',');
            timestamp = std::stoull(line_split.at(0));
            int x = std::stoi(line_split.at(2));
            int y = std::stoi(line_split.at(3));
            int z = std::stoi(line_split.at(4));
            if (saveFirstTimestamp and timestamp >=beginOfInterval){
                saveFirstTimestamp = false;
            }
            if (!saveFirstTimestamp) {

                if (timestamp - beginOfInterval >=  1000) {
                    return beginOfInterval+1000;
                }

                if (x > 0 and x < 53483 and y > -33960 and y < 33965) {
                    Debs::Position position(timestamp, x, y, z);
                    this->addPositionData(position);
                    chunkSize-=1;
                }
                if (chunkSize==0){
                    return timestamp;
                }
            }
    }
    std::cout << "Ball file is finished" << std::endl;
    return 14900000;
}



