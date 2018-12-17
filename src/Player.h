//
// Created by Francesco on 04/10/2018.
//
#include "Position.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#ifndef MIDDLEWARE_PLAYER_H
#define MIDDLEWARE_PLAYER_H

namespace Debs{
    class Player {
    private:
        std::string name;
        std::vector<Position> chunkOfPositions;
        std::ifstream *sensorFile = nullptr;
        int possessionTime;
        int ballTicks = 0;
        Position lastUsefullPosition = Debs::Position(0,0,0,0);
        unsigned long long int indexOfLastUsefullPosition = 0;

    public:
        Player(std::string, std::string );
        std::string getName();
        std::vector<Position> getChunkOfPositions();
        std::ifstream &getSensorFile();
        void addPositionData(Debs::Position);
        void chargeChunk(long long int,long long int);
        Position getPosition(long long int ballTimestamp);
        int getBallTicks();
        void addTick();
        void toString();
    };


}



#endif //MIDDLEWARE_PLAYER_H
