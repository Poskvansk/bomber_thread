#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <vector>
#include <semaphore.h>
#include "player.hpp"

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
    #include <termios.h>
#endif

// extern sem_t rendered;
// extern sem_t p1_sem;
// extern sem_t p2_sem;

void render(std::vector<Player>& players);

#endif //__RENDERER_HPP__