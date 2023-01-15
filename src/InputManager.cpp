#include "InputManager.hpp"

InputManager& InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}

InputManager::InputManager(){
    quitRequested = false;
    updateCounter = 0;
}

InputManager::~InputManager(){
}

void InputManager::Update(){
    SDL_Event event;
    quitRequested = false;
    updateCounter++;
    while (SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT)
			quitRequested = true;
        if(event.type == SDL_KEYDOWN && !event.key.repeat){
            keyState[event.key.keysym.sym] = true;
            keyUpdate[event.key.keysym.sym] = updateCounter;
        }
        if(event.type == SDL_KEYUP){
            keyState[event.key.keysym.sym] = false;
            keyUpdate[event.key.keysym.sym] = updateCounter;
        }   
    }
}

bool InputManager::KeyPress (int key){
    auto it = keyUpdate.find(key);
    if(it != keyUpdate.end()){
        if(it -> second == updateCounter)
            return keyState.find(key) -> second;
        return false;
    }
    return false;

}

bool InputManager::KeyRelease (int key){
    auto it = keyUpdate.find(key);
    if(it != keyUpdate.end()){
        if(it -> second == updateCounter)
            return !keyState.find(key) -> second;
        return false;
    }
    return false;
}

bool InputManager::IsKeyDown (int key){
    auto it = keyState.find(key);
    if(it != keyState.end())
        return it -> second;
    return false;
}

bool InputManager::QuitRequested (){
    return quitRequested;
}