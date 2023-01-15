#ifndef InputManager_HPP
#define InputManager_HPP
#define INCLUDE_SDL
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACEBAR SDLK_SPACE
#define W_KEY SDLK_w
#define S_KEY SDLK_s
#define A_KEY SDLK_a
#define D_KEY SDLK_d

#include <unordered_map>
#include <SDL2/SDL.h>
#include "InputManager.hpp"
// #include "SDL_include.h"


using namespace std;

class InputManager{
private:
    // bool mouseState[6];
    // int mouseUpdate[6];
    unordered_map<int, bool> keyState;
    unordered_map<int,int> keyUpdate;
    bool quitRequested;
    int updateCounter;
    // int mouseX;
    // int mouseY;

public:
    InputManager();
    ~InputManager();
    void Update ();
    bool KeyPress (int key);
    bool KeyRelease (int key);
    bool IsKeyDown (int key);
    // bool MousePress (int button);
    // bool MouseRelease (int button);
    // bool IsMouseDown (int button);
    // int  GetMouseX ();
    // int  GetMouseY ();
    bool QuitRequested ();
    static InputManager& GetInstance (); 
};

#endif