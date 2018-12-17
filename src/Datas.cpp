//
// Created by Francesco on 18/09/2018.
//

#include "Datas.h"
#include "Position.h"

#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std;

namespace Debs {

    /* Functions that insert to the vector of player, the sensors and the name of the player
     *
     * sensor: sensor of the player
     * player: player name
     */

    void PlayersData::addPlayerData(int sensor, std::string player) {
        this->players.insert({sensor, player});
        cout << "Add a player with him sensor " << player << " " << sensor << endl;
    }

    /*
     * Functions that return a player given him sensor
     *
     * sensor: sensor of the player
     *
     * return: player name
     */

    std::string PlayersData::isHimSensor(int sensor) {
        for ( auto it = this->players.begin(); it != this->players.end(); ++it ){
            if(it->first == sensor) {
                return it->second;
            }
        }
        return "";
    }

    /*
     * Getter of the listOfPlayer
     */

    vector<string> PlayersData::getListOfPlayer() {
        return this->listOfPlayer;
    }

    /*
     *  Function that popolate the listOfPlayer
     */

    void PlayersData::addPlayerToPlayerList() {
        this->listOfPlayer.emplace_back("Nick Gertje");
        this->listOfPlayer.emplace_back("Dennis Dotterweich");
        this->listOfPlayer.emplace_back("Niklas Waelzlein");
        this->listOfPlayer.emplace_back("Wili Sommer");
        this->listOfPlayer.emplace_back("Philipp Harlass");
        this->listOfPlayer.emplace_back("Roman Hartleb");
        this->listOfPlayer.emplace_back("Erik Engelhardt");
        this->listOfPlayer.emplace_back("Sandro Schneider");
        this->listOfPlayer.emplace_back("Kevin Baer");
        this->listOfPlayer.emplace_back("Luca Ziegler");
        this->listOfPlayer.emplace_back("Ben Mueller");
        this->listOfPlayer.emplace_back("Vale Reitstetter");
        this->listOfPlayer.emplace_back("Christopher Lee");
        this->listOfPlayer.emplace_back("Leon Heinze");
        this->listOfPlayer.emplace_back("Leo Langhans");
        this->listOfPlayer.emplace_back("Leon Krapf");

        for (auto v : this->listOfPlayer)
            std::cout << v << "\n";
    }

    /*
     * Constructor of PlayersData
     */

    PlayersData::PlayersData(void) {
        return;
    }

    /*
     * Getter of Players
     */

    std::unordered_map<int, std::string> PlayersData::getPlayerSensors() {
        return this->players;
    }

    /*
     * Function that add a sensor of the ball
     *
     * sensor: sensor of the ball to add
     */

    void BallData::addBallSensor(int sensor) {
        this -> ballSensor.push_back(sensor);
    }

    /*
     * Functions that return a boolean if the sensor in input is a ball sensor
     *
     * sensor: sensor of the ball
     *
     * return: true if the sensor is a sensor ball else false
     */

    bool BallData::isSensorBall(int sensor) {
        std::vector<int>::iterator it;
        it = std::find(this->ballSensor.begin(), this->ballSensor.end(), sensor);
        return !(it == this->ballSensor.end());
    }

    /*
     * Getter of ballSensor
     */

    std::vector<int> BallData::getBallSensor() {
        return this->ballSensor;
    }

    /*
     * Function that mapping the player with his relative team
     *
     * player: name of the player
     * team: enumeration representing the team
     *
     */

    void PlayersTeam::addPlayerToTeam(std::string player, Debs::Team team) {
        if (team == Debs::Team::A){
            this->team_A.push_back(player);
            return;
        }
        this->team_B.push_back(player);
    }

    /*
     * Functions that return a boolean if player belongs to the team in input
     *
     * player: name of the player
     * team: enumeration representing the team
     *
     * return: true player belongs to team else false
     */

    bool PlayersTeam::isOfTeam(std::string player, Team team) {
        if (team == Debs::Team::A){
            std::vector<std::string>::iterator it;
            it = std::find(this->team_A.begin(), this->team_A.end(), player);
            return !(it == this->team_A.end());
        }
        std::vector<std::string>::iterator it;
        it = std::find(this->team_B.begin(), this->team_B.end(), player);
        return !(it == this->team_B.end());
    }

    /*
     * Function that add a sensor of the referee
     *
     * sensor: sensor of the referee to add
     */

    void RefereeData::addSensor(int sensor) {
        this->refereeSensor.push_back(sensor);
        std::cout << "Add sensor "<< sensor << " to referee sensor" << std::endl;
    }

    /*
     * Functions that return a boolean if the sensor in input is a referee sensor
     *
     * sensor: sensor of the referee
     *
     * return: true if the sensor is a referee sensor else false
     */

    bool RefereeData::isRefereeSensor(int sensor) {
        std::vector<int>::iterator it;
        it = std::find(this->refereeSensor.begin(), this->refereeSensor.end(), sensor);
        return !(it == this->refereeSensor.end());
    }

    /*
     * Getter of the refereeSensor
     */

    std::vector<int> RefereeData::getRefereeSensor() {
        return this->refereeSensor;
    }

    /*
     * Function that save all the metadatas of the players, ball, referee and team
     *
     * return: struct of metadatas containing vectors of players, ball, referee and playersTeam
     */

    metadatas saveMetadatas() {
        PlayersData player;
        BallData ball;
        PlayersTeam playersTeam;
        RefereeData referee;

        player.addPlayerData(13, "Nick Gertje");
        player.addPlayerData(14, "Nick Gertje");
        player.addPlayerData(97, "Nick Gertje");
        player.addPlayerData(98, "Nick Gertje");
        player.addPlayerData(47, "Dennis Dotterweich");
        player.addPlayerData(16, "Dennis Dotterweich");
        player.addPlayerData(49, "Niklas Waelzlein");
        player.addPlayerData(88, "Niklas Waelzlein");
        player.addPlayerData(19, "Wili Sommer");
        player.addPlayerData(52, "Wili Sommer");
        player.addPlayerData(53, "Philipp Harlass");
        player.addPlayerData(54, "Philipp Harlass");
        player.addPlayerData(23, "Roman Hartleb");
        player.addPlayerData(24, "Roman Hartleb");
        player.addPlayerData(57, "Erik Engelhardt");
        player.addPlayerData(58, "Erik Engelhardt");
        player.addPlayerData(59, "Sandro Schneider");
        player.addPlayerData(28, "Sandro Schneider");

        player.addPlayerData(61, "Leon Krapf");
        player.addPlayerData(62, "Leon Krapf");
        player.addPlayerData(99, "Leon Krapf");
        player.addPlayerData(100, "Leon Krapf");
        player.addPlayerData(63, "Kevin Baer");
        player.addPlayerData(64, "Kevin Baer");
        player.addPlayerData(65, "Luca Ziegler");
        player.addPlayerData(66, "Luca Ziegler");
        player.addPlayerData(67, "Ben Mueller");
        player.addPlayerData(68, "Ben Mueller");
        player.addPlayerData(69, "Vale Reitstetter");
        player.addPlayerData(38, "Vale Reitstetter");
        player.addPlayerData(71, "Christopher Lee");
        player.addPlayerData(40, "Christopher Lee");
        player.addPlayerData(73, "Leon Heinze");
        player.addPlayerData(74, "Leon Heinze");
        player.addPlayerData(75, "Leo Langhans");
        player.addPlayerData(44, "Leo Langhans");

        ball.addBallSensor(4);
        ball.addBallSensor(8);
        ball.addBallSensor(10);
        ball.addBallSensor(12);

        playersTeam.addPlayerToTeam("Nick Gertje", Team::A);
        playersTeam.addPlayerToTeam("Dennis Dotterweich", Team::A);
        playersTeam.addPlayerToTeam("Niklas Waelzlein", Team::A);
        playersTeam.addPlayerToTeam("Wili Sommer", Team::A);
        playersTeam.addPlayerToTeam("Philipp Harlass", Team::A);
        playersTeam.addPlayerToTeam("Roman Hartleb", Team::A);
        playersTeam.addPlayerToTeam("Erik Engelhardt", Team::A);
        playersTeam.addPlayerToTeam("Sandro Schneider", Team::B);
        playersTeam.addPlayerToTeam("Leon Krapf", Team::B);
        playersTeam.addPlayerToTeam("Kevin Baer", Team::B);
        playersTeam.addPlayerToTeam("Luca Ziegler", Team::B);
        playersTeam.addPlayerToTeam("Ben Mueller", Team::B);
        playersTeam.addPlayerToTeam("Vale Reitstetter", Team::B);
        playersTeam.addPlayerToTeam("Christopher Lee", Team::B);
        playersTeam.addPlayerToTeam("Leon Heinze", Team::B);
        playersTeam.addPlayerToTeam("Leo Langhans", Team::B);

        referee.addSensor(105);
        referee.addSensor(106);
        player.addPlayerToPlayerList();
        return {player, ball, referee, playersTeam};
    }
};



