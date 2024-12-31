#include <SDL.h>
#include "initSnake.h"
#include "game.h"
#include "draw.h"


int main(int argc, char *argv[]) {
    game_t game = initGame();

    SDL_Surface *screen = SDL_GetWindowSurface(game.window);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game.renderer, screen);

    while (1) {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 128, 0));

        handleInput(&game);
        handleMovement(&game.snake);

        char text[100];
        sprintf(text, "Snake by wiKapo");
        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, game.charset);

        if (game.startTime) {
            sprintf(text, "%2d:%2d.%3d",
                    ((SDL_GetTicks() - game.startTime) / 1000) / 60,
                    ((SDL_GetTicks() - game.startTime) / 1000) % 60,
                    (SDL_GetTicks() - game.startTime) % 1000);
            DrawTime(screen, screen->w - 100, 10, text, game.charset);
        }

        DrawSnake(screen, game.snake.pos, game.snake.length, game.objects);
//        TestPrint(screen, game.objects);
        SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
        SDL_RenderCopy(game.renderer, texture, NULL, NULL);

        SDL_RenderPresent(game.renderer);

        SDL_Delay(100);
    }

    SDL_Quit();
    return 0;
}
