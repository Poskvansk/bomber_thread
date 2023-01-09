#ifndef __POSITION_HPP__
#define __POSITION_HPP__

struct Position {
    int x;
    int y;
    Position() : x(10), y(10) {};
    Position(int x, int y) : x(x), y(y) {};
};

#endif // __POSITION_HPP__