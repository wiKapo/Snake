#include <SDL.h>
#include "initSnake.h"
#include "game.h"
#include "draw.h"

int main(int argc, char *argv[]) {
    game_t game = initGame();
    uint32_t tickPrevious = 0, tickCurrent = 0, frameTime = 0, gameTime = 0, pauseTime = 0, accelerationTime = 0;

    SDL_Surface *screen = SDL_GetWindowSurface(game.window);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game.renderer, screen);

    const SDL_Rect gameBorder = {game.area.x - 8, game.area.y - 8, game.area.w + 16, game.area.h + 16};

    while (game.state != QUIT) {

        SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 64, 41, 5));

        DrawTopBar(screen, game.charset, gameTime, game.state, game.score);
        DrawColorBox(screen, game.charset, gameBorder, 0, SDL_MapRGB(screen->format, 0, 128, 0));

        if (DEBUG) {
            char text[100];
            sprintf(text, "HEAD POS X: %02d Y: %02d GAME ARENA squares %dx%d squares No %d", game.snake.pos->x,
                    game.snake.pos->y,
                    game.area.w / 32, game.area.h / 32, game.area.w / 32 * game.area.h / 32);
            DrawString(screen, game.charset, 10, 32, text);
            sprintf(text, "GAME ARENA %dx%d CONFIG WINDOW %dx%d", game.area.x, game.area.y,
                    game.config.width, game.config.height);
            DrawString(screen, game.charset, 10, 40, text);
            sprintf(text, "APPLE POS %dx%d SPEED %.02f", game.objectPos[APPLE].x, game.objectPos[APPLE].y,
                    game.snake.speed ? game.config.start_speed / (float)game.snake.speed : -99.9);
            DrawString(screen, game.charset, 10, 48, text);
            sprintf(text, "GAME STATE: %s", GetStateKey(game.state));
            DrawColorString(screen, game.charset, screen->w - (strlen(text) + 2) * 8, 48, text,
                            (SDL_Color) {200, 200, 0});
        }

        HandleInput(&game);

        switch (game.state) {
            case INFO:
                DrawHelp(screen, game.charset);
                break;
            case NEW_GAME:
                DrawGame(screen, game);
                frameTime = tickPrevious = gameTime = pauseTime = 0;
                break;
            case PLAY:
                tickCurrent = SDL_GetTicks() - game.startTime - pauseTime;
                frameTime += (tickCurrent - tickPrevious);
                accelerationTime += (tickCurrent - tickPrevious);
                gameTime += (tickCurrent - tickPrevious);
                tickPrevious = tickCurrent;

                DrawGame(screen, game);

                if (accelerationTime > game.config.acceleration_interval && game.snake.speed > game.config.max_speed) {
                    game.snake.speed -= game.config.acceleration;
                    accelerationTime -= game.config.acceleration_interval;
                } else if (game.snake.speed < game.config.max_speed) {
                    game.snake.speed = game.config.max_speed;
                }

                if (frameTime > game.snake.speed) {
                    HandleMovement(&game.snake, game.area);

                    CheckFruitCollision(&game);

                    if (CheckSelfCollision(&game.snake) || CheckBorderCollision(game.area, game.snake.pos[0]))
                        game.state = GAME_OVER;

                    game.deltaTime += game.snake.speed;
                    frameTime -= game.snake.speed;
                }
                break;
            case GAME_OVER:
                DrawGame(screen, game);
                DrawGameOver(screen, game.charset, game.score, game.deltaTime);
                break;
            case WIN:
                DrawGame(screen, game);
                DrawWin(screen, game.charset, game.score, game.deltaTime);
                break;
            case LOAD:
                DrawGame(screen, game);
                break;
            case PAUSE:
                DrawGame(screen, game);
                pauseTime = SDL_GetTicks() - game.startTime - tickPrevious;
                break;
            case PAUSE_INFO:
                DrawGame(screen, game);
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
