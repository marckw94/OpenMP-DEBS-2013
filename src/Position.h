//
// Created by Francesco on 04/10/2018.
//
#include <math.h>
#ifndef MIDDLEWARE_POSITION_H
#define MIDDLEWARE_POSITION_H

namespace Debs {

    class Position {

    private:
        long long int timestamp;
        int x;
        int y;
        int z;

    public:
        Position(long long int timestamp, int x, int y, int z);
        int getX();
        int getY();
        int getZ();
        long long int getTimestamp();
        double getDistance(Position ballPosition);
        void toString();
    };


}




#endif //MIDDLEWARE_POSITION_H
