//
// Created by Francesco on 18/09/2018.
//
#include "Position.h"

#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include <list>
namespace Debs {

    class PlayersData {


    public:
        void addPlayerData(int sensor, std::string player);
        std::vector<std::string> getListOfPlayer();
        void addPlayerToPlayerList();
        PlayersData();
        std::unordered_map<int, std::string> getPlayerSensors();
        std::string isHimSensor(int sensor);


    private:
        std::unordered_map<int, std::string> players = {};
        std::vector<std::string>  listOfPlayer = {};


    };

    class BallData {
    private:
        std::vector<int> ballSensor = {};
        std::vector<Position> ballPositions = {};


    public:
        void addBallSensor(int sensor);
        std::vector<int> getBallSensor();
        bool isSensorBall(int sensor);
    };

    enum class Team {
        A = 1, B
    };

    class PlayersTeam {

    private:
        std::vector<std::string> team_A = {};
        std::vector<std::string> team_B = {};

    public:
        void addPlayerToTeam(std::string, Team team);

        bool isOfTeam(std::string, Team team);

    };

    class RefereeData{
    private:
        std::vector<int> refereeSensor = {};

    public:
        void addSensor(int sensor);
        bool isRefereeSensor(int sensor);
        std::vector<int> getRefereeSensor();
    };
    struct metadatas {
        PlayersData player;
        BallData ball;
        RefereeData referee;
        PlayersTeam teams;
    };

    metadatas saveMetadatas();

}
#ifndef MIDDLEWARE_DATAS_H
#define MIDDLEWARE_DATAS_H

#endif //MIDDLEWARE_DATAS_H
