#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <vector>
#include "player.hpp"

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
    #include <termios.h>
#endif

void render(std::vector<Player>& players);

#endif //__RENDERER_HPP__