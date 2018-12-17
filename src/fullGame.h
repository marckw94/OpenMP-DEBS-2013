//
// Created by Francesco on 27/09/2018.
//
#include <iostream>
#include "Datas.h"
#include "Utils.h"
#include "Interruption.h"
#ifndef MIDDLEWARE_FULLGAME_H
#define MIDDLEWARE_FULLGAME_H

namespace Debs {


    class fullGame {
    public:
        void fullGameInitialize(std::string path, Debs::metadatas, Debs::Interruption);
        bool gameIsStart(unsigned long long int i);

        bool gameNotStop(unsigned long long int timestamp, long long int half);

        bool gameIsEnd(unsigned long long int i);

        bool gameNotStop(unsigned long long int timestamp, long long int half, int whatHalf);
    };


#endif //MIDDLEWARE_FULLGAME_H
}