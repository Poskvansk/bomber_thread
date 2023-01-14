#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <string>

struct Position {
    int x;
    int y;
    Position() : x(10), y(10) {};
    Position(int x, int y) : x(x), y(y) {};
};

class Player {
    private:
        std::string name;
        int score;

    public:
        char skin;
        Position pos;
        Player(std::string name) : name(name), score(0), skin('Y') {};
        ~Player();

        void setName(std::string& name);
        std::string getName();
        
        void setScore(int score);
        int getScore();
};

#endif // __PLAYER_HPP__