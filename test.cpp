#include <iostream>
#include <thread>
#include <string>
#include <mutex>

#include "./include/InputManager.hpp"


using namespace std;

mutex mtx_input;
    InputManager inputManager = InputManager::GetInstance();

void inputThread(string name) {
    int up, down, left, right, grab;
    if(name == "Player 1") {
        up = SDLK_w;
        down = SDLK_s;
        left = SDLK_a;
        right = SDLK_d;
        grab = SDLK_SPACE;
    }
    else {
        up = SDLK_UP;
        down = SDLK_DOWN;
        left = SDLK_LEFT;
        right = SDLK_RIGHT;
        grab = SDLK_RETURN;
    }

    while(!inputManager.QuitRequested()) {

        inputManager.Update();

        if(inputManager.IsKeyDown(up)) {
            cout << name << " moved up" << endl;
        }
        if(inputManager.IsKeyDown(down)) {
            cout << name << " moved down" << endl;
        }
        if(inputManager.IsKeyDown(left)) {
            cout << name << " moved left" << endl;
        }
        if(inputManager.IsKeyDown(right)) {
            cout << name << " moved right" << endl;
        }
        if(inputManager.IsKeyDown(grab)) {
            cout << name << " grabbed a bomb" << endl;
        }
        if(inputManager.IsKeyDown(SDLK_ESCAPE)) {
            break;
        }
        SDL_Delay(100);
    }
}

int main(int argc, char const *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Bomberman", 0 , 0, 0, 0, SDL_WINDOW_BORDERLESS);
    //minimize window
    // SDL_MinimizeWindow(window);
    
    string name = "Player 1";
    thread t1(inputThread, name);

    string name2 = "Player 2";
    thread t2(inputThread, name2);

    t1.join();
    t2.join();
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
