//
// Created by Francesco on 15/11/2018.
//
#include "Position.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#ifndef MIDDLEWARE_BALL_H
#define MIDDLEWARE_BALL_H

namespace Debs {
    class Ball {
    private:
        std::vector<Position> chunkOfPositions;
        std::ifstream *sensorFile = nullptr;

    public:
        Ball(std::string);
        std::vector<Position> getChunkOfPositions();
        void addPositionData(Debs::Position);
        std::ifstream &getSensorFile();
        long long int chargeChunk(long long int);
    };
}


#endif //MIDDLEWARE_BALL_H
