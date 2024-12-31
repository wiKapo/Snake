#include <SDL.h>
#include "initSnake.h"
#include "game.h"
#include "draw.h"

#define CONFIG_PATH     "../config.txt" //with cmake '../' is required

const point_t testPos[19] = {
        {4, 2},
        {3, 2},
        {2, 2},
        {2, 3},
        {2, 4},
        {3, 4},
        {4, 4},
        {4, 5},
        {3, 5},
        {2, 5},
        {1, 5},
        {1, 6},
        {1, 7},
        {1, 8},
        {1, 9},
        {2, 9},
        {3, 9},
        {3, 8},
        {3, 7},
};

int main(int argc, char *argv[]) {
    game_t game;
    game.config = read_config(CONFIG_PATH);
    if (DEBUG) {
        game.snake.pos = testPos;
        game.snake.length = sizeof(testPos) / sizeof(*testPos);
    }

    initSDL(game.config, &game);
    initAssets(&game);


    SDL_Surface *screen = SDL_GetWindowSurface(game.window);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game.renderer, screen);
    SDL_Rect rect = {10, 10, 100, 100};

    while (1) {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 128, 0));

        char text[100];
        sprintf(text, "Snake by wiKapo");
        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, game.charset);

        DrawSnake(screen, game.snake.pos, game.snake.length, game.objects);
//        TestPrint(screen, game.objects);
        SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
        SDL_RenderCopy(game.renderer, texture, NULL, NULL);

        SDL_RenderPresent(game.renderer);
        getInput();

        SDL_Delay(50);
    }

    SDL_Quit();
    return 0;
}
