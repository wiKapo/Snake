#include <SDL.h>
#include "initSnake.h"
#include "game.h"
#include "draw.h"

#define PADDING     40

int main(int argc, char *argv[]) {
    game_t game = initGame();
    uint32_t tickPrevious = 0, tickCurrent = 0, frameTime = 0, gameTime = 0, pauseTime = 0;

    SDL_Surface *screen = SDL_GetWindowSurface(game.window);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game.renderer, screen);

    const SDL_Rect gameArea = {PADDING, 30 + PADDING, ((screen->w) / 32 - 2) * 32, ((screen->h - 30) / 32 - 2) * 32};
    const SDL_Rect gameBorder = {gameArea.x - 7, gameArea.y - 7, gameArea.w + 16, gameArea.h + 16};

    while (game.state != QUIT) {

        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 64, 41, 5));

        DrawTopBar(screen, game.charset, gameTime, game.state, game.score);
        DrawColorBox(screen, game.charset, gameBorder, 0, SDL_MapRGB(screen->format, 0, 128, 0));

        if (DEBUG) {
            char text[100];
            sprintf(text, "HEAD POS X: %d Y: %d GAME ARENA W: %d H: %d", game.snake.pos->x, game.snake.pos->y,
                    gameArea.w / 32, gameArea.h / 32);
            DrawString(screen, game.charset, 50, 150, text);
        }

        HandleInput(&game);
        DrawSnake(screen, game.objects, gameArea, game.snake.pos, game.snake.length);

        switch (game.state) {
            case INFO:
                DrawHelp(screen, game.charset);
                break;
            case NEW_GAME:
                frameTime = tickPrevious = gameTime = pauseTime = 0;
                break;
            case PLAY:
                tickCurrent = SDL_GetTicks() - game.startTime - pauseTime;
                frameTime += (tickCurrent - tickPrevious);
                gameTime += (tickCurrent - tickPrevious);
                tickPrevious = tickCurrent;

                int snakeSpeed = 200; //TODO connect with game config
                if (frameTime > snakeSpeed) {
                    HandleMovement(&game.snake, gameArea);

                    if (CheckCollision(&game.snake) || CheckBorderCollision(gameArea, game.snake.pos[0]))
                        game.state = GAME_OVER;

                    game.deltaTime += snakeSpeed;
                    frameTime -= snakeSpeed;
                }
                break;
            case GAME_OVER:
                DrawGameOver(screen, game.charset, 12345, game.deltaTime);
                break;
            case WIN:
                DrawWin(screen, game.charset, 99999, game.deltaTime);
                break;
            case LOAD:
                break;
            case PAUSE:
                pauseTime = SDL_GetTicks() - game.startTime - tickPrevious;
                break;
            case PAUSE_INFO:
                pauseTime = SDL_GetTicks() - game.startTime - tickPrevious;
                DrawHelp(screen, game.charset);
                break;
            case QUIT:
                break;
        }
        SDL_UpdateTexture(texture, nullptr, screen->pixels, screen->pitch);
        SDL_RenderCopy(game.renderer, texture, nullptr, nullptr);

        SDL_RenderPresent(game.renderer);
    }
    SDL_Quit();
    return 0;
}
