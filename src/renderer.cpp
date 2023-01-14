#include "renderer.hpp"

sem_t rendered;

void print_infos(std::vector<Player>& players) {

    std::cout << "player " << players[0].getName() << " position " << players[0].pos.x << " " << players[0].pos.y << " direction " << players[0].getDirection()
    << " hasbomb " << players[0].getHasBomb();
    std::cout << "               ";
    std::cout << "player " << players[1].getName() << " position " << players[1].pos.x << " " << players[1].pos.y << " direction " << players[1].getDirection()
    << " hasbomb " << players[1].getHasBomb() << std::endl;

    std::cout << "bomb " << bombs[0].pos.x << " " << bombs[0].pos.y << " holded by " << bombs[0].getHoldedBy() << std::endl;

}

void print_map(std::vector<Player>& players) {

    // sem_wait(&rendered);

    for (size_t i = 0; i < MAP_HEIGHT; i++) {
        for (size_t j = 0; j < MAP_WIDTH; j++) {

            bool cell_printed = false; // POR Q???

            for (size_t k = 0; k < players.size(); k++) {
                if(i == players[k].pos.y && j == players[k].pos.x) {
                    std::cout << players[k].skin;
                    cell_printed = true;
                    // continue;
                }
            }

            for (size_t k = 0; k < bombs.size(); k++) {
                if(i == bombs[k].pos.y && j == bombs[k].pos.x) {
                    std::cout << bombs[k].skin;
                    cell_printed = true;
                    // continue;
                }
            }

            if (cell_printed) continue; // POR QUE ISSO FUNCIONA???

            if (i == 0 || i == MAP_HEIGHT - 1) std::cout << "=";

            else if (j == 0 || j == MAP_WIDTH - 1) std::cout << "|";

            else if(i % 5 == 0 && j % 15 == 0) {
                for(int k = 0; k < 3; k++) {
                    std::cout << "+";
                }
                j += 2;
            }

            else std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    print_infos(players);
    // sem_post(&rendered);
}


void render(std::vector<Player>& players) {

    while (!game_over) {
        system(CLEAR);
        print_map(players);
        usleep(8000); //
    }
}
