#include <sys/time.h>
#include <iostream>
#include <omp.h>
#include <time.h>
#include "fullGame.h"
#include "Utils.h"
#include "Player.h"
#include "Ball.h"
#include <chrono>

/*
 * Function that do the analysis,
 *
 * timeOutput: period of time for print the partial results
 * maxDistance: maximum distance usefull for the analysis
 * playerList: list of all the player
 * nthreads: number of thread we want to use
 * metadatas: metadatas of the game
 *
 */

void run(int timeOutput, int maxDistance, std::vector<Debs::Player *> playerList, int nthreads, Debs::metadatas metadatas) {
    timeOutput = timeOutput ;
    auto originalTimeOutput = timeOutput;
    int numberOfPrint = 0;
    bool gameEnd = false;
    Debs::Ball *ball = new Debs::Ball("../../../Desktop/Middleware");
    long long int beginOfInterval = 10756385;
    long long int nextBegin = 0;
    std::cout << "The Analysis is started " << std::endl;
    while (!gameEnd) {
        #pragma omp parallel num_threads(nthreads)
        {
        #pragma omp single
            {
                nextBegin = ball->chargeChunk(beginOfInterval);
        }
        #pragma omp for schedule(dynamic)
            for (unsigned long long int i = 0; i < playerList.size();i++){
                auto p = playerList.at(i);

                p->chargeChunk(beginOfInterval, nextBegin);
            }
		};

        #pragma omp parallel num_threads(nthreads)
        {
            #pragma omp for ordered schedule(static, 1)
            for (int i = 0; i < ball->getChunkOfPositions().size(); i = i + 1) {
                auto b = ball->getChunkOfPositions().at(i);
                auto ballTimestamp = b.getTimestamp();
                double distance = maxDistance;
                Debs::Player *nearPlayer = nullptr;
                for (unsigned long long int j = 0; j < playerList.size(); j++) {
                    auto p = playerList.at(j);
                    auto position = p->getPosition(ballTimestamp);
                    auto playerDistance = position.getDistance(b);
                    if (playerDistance < distance) {
                        distance = playerDistance;
                        nearPlayer = p;
                    }
                }
                if (nearPlayer != nullptr) {
                    #pragma omp ordered
                    {
                        nearPlayer->addTick();
                    };
                }
            }
        };
        timeOutput = timeOutput - 1;
        int ticksTeamA = 0;
        int ticksTeamB = 0;
        if (timeOutput == 0){
            numberOfPrint = numberOfPrint + 1;
            std::cout << "Time of the match = " << Utils::fromSecondToTime(originalTimeOutput*numberOfPrint) << std::endl;
            for (int i = 0; i < playerList.size(); i++) {
                std::cout << "Possession time of " << playerList.at(i)->getName() << " "
                          << Utils::fromMilliToTime(playerList.at(i)->getBallTicks()) << std::endl;
                if(metadatas.teams.isOfTeam(playerList.at(i)->getName(), Debs::Team::A)){
                    ticksTeamA = ticksTeamA + playerList.at(i)->getBallTicks();
                }
                else{
                    ticksTeamB = ticksTeamB + playerList.at(i)->getBallTicks();
                }
            }
            std::cout << "Total ticks team A = " << Utils::fromMilliToTime(ticksTeamA) << std::endl;
            std::cout << "Total ticks team B = " << Utils::fromMilliToTime(ticksTeamB) << std::endl;
            std::cout << "\n";
            timeOutput = originalTimeOutput;

        }
        if (nextBegin >= 14879639){
            gameEnd = true;
        }
        beginOfInterval = nextBegin;
	}
	numberOfPrint = numberOfPrint + 1;
    int ticksTeamA = 0;
    int ticksTeamB = 0;
    std::cout << "End game results" << std::endl;
    for (int i = 0; i < playerList.size(); i++){
        std::cout << "Possession time of "<< playerList.at(i)->getName() << " " << Utils::fromMilliToTime(playerList.at(i)->getBallTicks()) << std::endl;
        if(metadatas.teams.isOfTeam(playerList.at(i)->getName(), Debs::Team::A)){
            ticksTeamA = ticksTeamA + playerList.at(i)->getBallTicks();
        }
        else{
            ticksTeamB = ticksTeamB + playerList.at(i)->getBallTicks();
        }
    }
    std::cout << "Total ticks team A = " << Utils::fromMilliToTime(ticksTeamA) << std::endl;
    std::cout << "Total ticks team B = " << Utils::fromMilliToTime(ticksTeamB) << std::endl;
    std::cout << "NumberOfPrint = " <<numberOfPrint << std::endl;
}

int main () {
    Debs::metadatas meta;
    Debs::PlayersData().addPlayerToPlayerList();
    meta = Debs::saveMetadatas();
    auto list = meta.player.getListOfPlayer();
    std::vector<Debs::Player*> playersList = {};
    int t = 0;
    int k = 0;
    while(t <= 0 or t > 60) {
        std::cout << "Write the parameter T " << std::endl;
        std::cin >> t ;
        std::cin.clear();
        if (t <= 0 or t > 60){
            while (std::cin.get() != '\n')
                continue;
            std::cout << "[ERROR] Parameter T must be an integer from 0 to 60" << std::endl;
        }

    }
    while(k <= 0 or k > 5) {
        std::cout << "Write the parameter K" << std::endl;
        std::cin >> k;
        std::cin.clear();
        if (k < 0 or k > 5){
            while (std::cin.get() != '\n')
                continue;
            std::cout << "[ERROR] Parameter K must be an integer from 0 to 5" << std::endl;
            k = 0;
        }
    }
    for (auto v : list){
        auto player =  new Debs::Player(v,"../../../Desktop/Middleware");
        playersList.push_back(player);
    }

    Debs::Interruption interruption;
    interruption.addInterruptionInterval("../../../Desktop/Middleware");
    Debs::fullGame fullGame;
    fullGame.fullGameInitialize("../../../Desktop/Middleware",meta ,interruption);
    int i = 8;
    timeval start, stop;
    double elapsedTime;
    gettimeofday(&start, NULL);
    run(t, k, playersList, i, meta);
    gettimeofday(&stop, NULL);
    elapsedTime = (stop.tv_sec - start.tv_sec) * 1000.0;               // sec to ms
    elapsedTime += (stop.tv_usec - start.tv_usec) / 1000.0;
    std::cout << "Time of analysis = " <<  Utils::fromMilliToTime(elapsedTime) <<
    " number of thread = " << i << std::endl;
    return 0;
}
