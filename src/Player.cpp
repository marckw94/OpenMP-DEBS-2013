//
// Created by Francesco on 04/10/2018.
//
#include <vector>
#include "Player.h"

/*
 * Getter of the name
 */

std::string Debs::Player::getName() {
    return this->name;
}

/*
 * Getter of chunkOfPositions
 */

std::vector<Debs::Position> Debs::Player::getChunkOfPositions() {
    return this->chunkOfPositions;
}

/*
 * Getter of ballTicks
 */

int Debs::Player::getBallTicks() {
    return this->ballTicks;
}

/*
 * Getter of sensorFile
 */

std::ifstream& Debs::Player::getSensorFile() {
    return *this->sensorFile;
}

/*
 * Constructor of a Player
 */

Debs::Player::Player(std::string name, std::string path) {
    this->name = name;
    this->sensorFile = new std::ifstream(path+ "/sensors/" + name + ".csv");
}

/*
 * Function that charge the chunk of the player with 1 second of datas takes from the file of the relative player
 *
 * beginOfInterval: first timestamp to analyze
 * endOfInterval: last timestamp to analyze
 */

void Debs::Player::chargeChunk(long long int beginOfInterval, long long endOfInterval) {
    this->chunkOfPositions.clear();
    this->indexOfLastUsefullPosition = 0;
    //this->lastUsefullPosition = Debs::Position(0,0,0,0);
    bool saveFirstTimestamp = true;
    std::string line;
    long long int timestamp;
    while(std::getline(this->getSensorFile(), line)) {
        std::vector<std::string> line_split = Utils::split_string(line, ',');
        timestamp = std::stoull(line_split.at(0));
        int x = std::stoi(line_split.at(2));
        int y = std::stoi(line_split.at(3));
        int z = std::stoi(line_split.at(4));
        if (saveFirstTimestamp and timestamp >= beginOfInterval) {
            saveFirstTimestamp = false;
        }
        if(!saveFirstTimestamp) {
            if (timestamp>endOfInterval){
                return;
            }
            Debs::Position position(timestamp, x, y, z);
            this->addPositionData(position);
        }
    }
    std::cout<< this->getName() << " file is finished" << std::endl;
    this->getSensorFile().close();
}

/*
 * Function that add the position in input to the relative players's chunk of position
 *
 * position: position to add to the chunk
 */

void Debs::Player::addPositionData(Debs::Position position) {
    this->chunkOfPositions.push_back(position);
}

/*
 * Function that return the nearest positions with a timestamp minor or equal to the ballTimestamp in input
 *
 * ballTimestamp: upperbound of the timestamp fot the position we want to retrieve
 *
 * return: position if it exist else a position of (0,0,0)
 */

Debs::Position Debs::Player::getPosition(long long int ballTimestamp) {
    auto positions = this->getChunkOfPositions();
    for (auto i = this->indexOfLastUsefullPosition; i < positions.size(); i++) {
        if (positions.at(i).getTimestamp() == ballTimestamp){
            this->lastUsefullPosition = positions.at(i);
            this->indexOfLastUsefullPosition = i;
            return positions.at(i);
        }

        if (positions.at(i).getTimestamp() > ballTimestamp ){
           return this->lastUsefullPosition;
        }
    }
    return Debs::Position(0,0,0,0);
}

/*
 * Function that add a tick of 1 to ballTicks
 */

void Debs::Player::addTick() {
    this->ballTicks = this->ballTicks + 1;
}

/*
 * ToString of the player (used for testing)
 */

void Debs::Player::toString() {
    std::cout << this->name << " number of ticks = " << this->ballTicks << std::endl;
}





