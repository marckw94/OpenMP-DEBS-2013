//
// Created by Francesco on 04/10/2018.
//
#include <iostream>
#include <math.h>
#include "Position.h"

/*
 * Constructor of Position class
 */

Debs::Position::Position(long long int timestamp, int x, int y, int z) {
    this->timestamp = timestamp;
    this->x = x;
    this->y = y;
    this->z = z;
}

/*
 * Getter of x position
 */

int Debs::Position::getX() {
    return this->x;
}

/*
 * Getter of y position
 */

int Debs::Position::getY() {
    return this->y;
}

/*
 * Getter of z position
 */

int Debs::Position::getZ() {
    return this->z;
}

/*
 * Getter of timestamp
 */

long long int Debs::Position::getTimestamp() {
    return this->timestamp;
}

/*
 * Function that calculate the distance from the position in input
 *
 * ballPosition: position for calculate the distance
 *
 * return: double represent the distance
 */

double Debs::Position::getDistance(Position ballPosition) {
    auto xx = (this->x - ballPosition.getX())*(this->x - ballPosition.getX());
    auto yy = (this->y - ballPosition.getY())*(this->y - ballPosition.getY());
    auto zz = (this->z - ballPosition.getZ())*(this->z - ballPosition.getZ());
    double result = xx + yy + zz;
    result = sqrt(result)/1000;
    return result;
}

/*
 * ToString of the position (Use for testing)
 */

void Debs::Position::toString() {
    std::cout << "Timestamp : " << this->timestamp  << "\n"<<
    "x : " << this->x << "\n" << "y : " << this->y << "\n"<<
    "z : " << this->z << std::endl;
}

