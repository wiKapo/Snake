#include "game.h"

void getInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_Quit();
                    exit(0);
                } else if (event.key.keysym.sym == SDLK_n) {
                    //restartGame();
                } else if (event.key.keysym.sym == SDLK_s) {
                    //quickSave();
                } else if (event.key.keysym.sym == SDLK_l) {
                    //quickLoad();
                } else {
                    //handleMovement();
                }
                break;
            default:
                break;
        }
    }
}