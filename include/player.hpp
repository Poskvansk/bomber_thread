#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <mutex>
// #include <pthread.h>
// #include <semaphore.h>

#include "position.hpp"
#include "input.hpp"
#include "bomb.hpp"

extern std::unordered_map<std::string, int> player_id;
extern std::vector<Bomb> bombs;

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;
extern bool game_over;

extern std::mutex p1_mtx;
// std::mutex p2_mtx;

// extern sem_t p1_sem;
// extern sem_t p2_sem;
// extern sem_t rendered;

class Player {
    private:
        std::string name;
        int score;
        char direction;
        bool alive;
        bool hasBomb;

    public:
        char skin;
        Position pos;

        Player(std::string name, char skin);
        ~Player();

        void setName(std::string& name);
        std::string getName();
        
        void setScore(int score);
        int getScore();

        void setDirection(char direction);
        char getDirection();

        bool getHasBomb();

        void move();

        void grabBomb();
};

#endif // __PLAYER_HPP__