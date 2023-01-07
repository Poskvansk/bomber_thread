#include <iostream>
#include <vector>
#include <string>

#include <thread>
#include <mutex>

//////////////////////////////////////////
#include "player.hpp"
#include "bomb.hpp"
//////////////////////////////////////////
using namespace std;

// #include <ncurses.h>

Position p(5,5);
Bomb bomb1(&p, 10);

vector<Player> players;

mutex mtx_input;



#ifdef _WIN32
    #define CLEAR "cls"

#else
    #define CLEAR "clear"
    #include <termios.h>
#endif

int MAP_WIDTH = 150;
int MAP_HEIGHT = 15;

////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>


#ifndef _WIN32
    int kbhit(){
        struct termios oldt, newt;
        int ch, oldf;
        tcgetattr(STDIN_FILENO,&oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        if(ch != EOF){
            ungetc(ch,stdin);
            return 1;
        }
        return 0;
    }
    int getch(void) {
        int ch;
        struct termios oldt;
        struct termios newt;
        tcgetattr(STDIN_FILENO,&oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

#else
    #include <conio.h>
#endif

////////////////////////////////////////////////////////////////////////////////

void print_map(vector<Player>& players) {


    for (size_t i = 0; i < MAP_HEIGHT; i++) {
        
        for (size_t j = 0; j < MAP_WIDTH; j++) {

            bool cell_printed = false; // POR Q???

            for (size_t k = 0; k < players.size(); k++) {
                if(i == players[k].pos.y && j == players[k].pos.x) {
                    cout << players[k].skin;
                    cell_printed = true;
                    // continue;
                }
            }

            if (cell_printed) continue; // POR QUE ISSO FUNCIONA???

            if(i == bomb1.pos->y && j == bomb1.pos->x) {
                cout << bomb1.skin;
                continue;
            }

            if (i == 0 || i == MAP_HEIGHT - 1) {
                cout << "=";
            } 
            else {
                if (j == 0 || j == MAP_WIDTH - 1) 
                    cout << "|";

                else cout << " ";
            }
        }
        cout << endl;
    }
    
    cout << endl;
}

void update(Player& player1) {

    while (true) {
    
        mtx_input.lock();
        
        if (kbhit()) {
            char input = getch();  // Read a keystroke without waiting
            if (input == 'w') player1.pos.y--;
            else if (input == 's') player1.pos.y++;
            else if (input == 'a') player1.pos.x--;
            else if (input == 'd') player1.pos.x++;
        }

        mtx_input.unlock();

        if (player1.pos.x < 1) player1.pos.x = 1;
        if (player1.pos.x > MAP_WIDTH - 2) player1.pos.x = MAP_WIDTH - 2;
        if (player1.pos.y < 1) player1.pos.y = 1;
        if (player1.pos.y > MAP_HEIGHT - 2) player1.pos.y = MAP_HEIGHT - 2;

        // check_collision();
    }
}

void render(Player& player1, Player& player2) {

    vector<Player> players = {player1, player2};
    while (true) {
    
        system(CLEAR);
        print_map(players);
        usleep(80000); // 100ms delay
    
    }
    

    return;
}

void game_loop(Player& player) {
    
    while (true) {

    
        cout << player.getName() << endl;
    //     update(player);

    //     render(players);
    }

}

int main(int argc, char const *argv[]) {
    

    struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    
    Player player1("Fulano");
    Player player2("Beltrano");
    players = {player1, player2};

    // game_loop(players);
    thread t1(update, ref(player1));
    thread t2(update, ref(player2));
    thread render_thread(render, ref(player1), ref(player2));


    t1.join();
    t2.join();
    render_thread.join();

    return 0;
}
