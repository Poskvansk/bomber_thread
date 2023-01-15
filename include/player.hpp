#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <SDL2/SDL.h>

#include "position.hpp"
#include "input.hpp"
#include "bomb.hpp"
#include "InputManager.hpp"

extern std::unordered_map<std::string, int> player_id;
extern std::vector<Bomb> bombs;

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;
extern bool game_over;

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

        Player(std::string name, char skin) : name(name), score(0), skin(skin) {};
        ~Player();

        void setName(std::string& name);
        std::string getName();
        
        void setScore(int score);
        int getScore();

        void setDirection(char direction);
        char getDirection();

        bool getHasBomb();

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void grabBomb();
};

#endif // __PLAYER_HPP__