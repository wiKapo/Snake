#include <SDL.h>
#include "initSnake.h"
#include "game.h"
#include "draw.h"
#include "colors.h"

int main(int argc, char *argv[]) {
    game_t game = initGame();
    //There has to be a better way to do this      V               V              V               V                     V...
    uint32_t tickPrevious = 0, tickCurrent = 0, frameTime = 0, gameTime = 0, pauseTime = 0, accelerationTime = 0, animationTime = 0;
    int delta = 0;

    SDL_Surface *screen = SDL_GetWindowSurface(game.window);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game.renderer, screen);

    const SDL_Rect gameBorder = {game.area.x - 8, game.area.y - 8, game.area.w + 16, game.area.h + 16};

    while (game.state != QUIT) {

        FillScreen(screen, BROWN);

        DrawTopBar(screen, game.charset, gameTime, game.state, game.score);
        DrawColorBox(screen, game.charset, gameBorder, 0, GRASS);

        if (DEBUG) {
            char text[100];
            //TOP DEBUG
            sprintf(text, "SNAKE: HEAD %02dx%02d SPEED %f MOVE TIME %d LENGTH %d",
                    game.snake.pos->x, game.snake.pos->y, game.config.start_speed / (float) game.snake.speed,
                    game.snake.speed, game.snake.length);
            DrawString(screen, game.charset, 10, 32, text);
            sprintf(text, "GAME AREA %02dx%02d WINDOW SIZE %dx%d", game.area.w / 32, game.area.h / 32,
                    game.config.width, game.config.height);
            DrawString(screen, game.charset, 10, 40, text);
            sprintf(text, "GAME STATE: %s", GetStateKey(game.state));
            DrawColorString(screen, game.charset, screen->w - (strlen(text) + 2) * 8, 48, text, YELLOW);

            //BOTTOM DEBUG
            if (game.orangeTimer > 0)
                sprintf(text, "ORANGE TIMER %d ORANGE CHANCE %d ORANGE PROGRESS %.2f",
                        game.orangeTimer, game.config.orange_chance,
                        game.orangeTimer / (float) game.config.orange_delay);
            else sprintf(text, "ORANGE TIMER %d ORANGE CHANCE %d", game.orangeTimer, game.config.orange_chance);
            DrawString(screen, game.charset, 10, screen->h - 16, text);

            sprintf(text, "APPLE POS %02dx%02d ORANGE POS %02dx%02d",
                    game.objectPos[APPLE].x, game.objectPos[APPLE].y,
                    game.objectPos[ORANGE].x, game.objectPos[ORANGE].y);
            DrawString(screen, game.charset, 10, screen->h - 8, text);
        }

        HandleInput(&game);

        switch (game.state) {
            case INFO:
                DrawHelp(screen, game.charset);
                break;
            case NEW_GAME:
                DrawGame(screen, game, &animationTime);
                frameTime = tickPrevious = gameTime = pauseTime = accelerationTime = animationTime = 0;
                break;
            case PLAY:
                tickCurrent = SDL_GetTicks() - game.startTime - pauseTime;
                delta = tickCurrent - tickPrevious;
                // me no likey
                frameTime += delta;
                accelerationTime += delta;
                gameTime += delta;
                animationTime += delta;
                //eugh ^

                if (game.orangeTimer < 0) {
                    game.orangeTimer += delta;
                    if (game.orangeTimer == 0)
                        if (rand() % 100 < game.config.orange_chance) {
                            PlaceObject(&game, ORANGE);
                            game.orangeTimer = game.config.orange_delay;
                        } else game.orangeTimer = -game.config.orange_delay / 2;
                } else if (game.orangeTimer > 0) {
                    DrawProgressBar(
                            screen, game.charset,
                            (SDL_Rect) {game.area.x - 8, game.area.y - 16, game.area.w + 16, 8},
                            game.orangeTimer, game.config.orange_delay, ORANGE_COLOR);
                    game.orangeTimer -= delta;
                    if (game.orangeTimer == 0) {
                        RemoveObject(&game, ORANGE);
                        game.orangeTimer = -game.config.orange_delay;
                    }
                }

                tickPrevious = tickCurrent;

                DrawGame(screen, game, &animationTime);

                if (accelerationTime > game.config.acceleration_interval && game.snake.speed > game.config.max_speed) {
                    game.snake.speed *= game.config.acceleration;
                    accelerationTime -= game.config.acceleration_interval;
                } else if (game.snake.speed < game.config.max_speed) {
                    game.snake.speed = game.config.max_speed;
                }

                if (frameTime > game.snake.speed) {
                    game.deltaTime += game.snake.speed;
                    frameTime -= game.snake.speed;

                    HandleMovement(&game.snake, game.area);

                    CheckFruitCollision(&game);
                    if (game.snake.length == game.area.w / 32 * game.area.h / 32) game.state = WIN;
                    else if (CheckSelfCollision(&game.snake) || CheckBorderCollision(game.area, game.snake.pos[0]))
                        game.state = GAME_OVER;
                }
                break;
            case GAME_OVER:
                DrawGame(screen, game, &animationTime);
                DrawGameOver(screen, game.charset, game.score, game.deltaTime);
                break;
            case WIN:
                DrawGame(screen, game, &animationTime);
                DrawWin(screen, game.charset, game.score, game.deltaTime);
                break;
            case LOAD:
                DrawGame(screen, game, &animationTime);
                if (game.orangeTimer > 0)
                    DrawProgressBar(
                            screen, game.charset,
                            (SDL_Rect) {game.area.x - 8, game.area.y - 16, game.area.w + 16, 8},
                            game.orangeTimer, game.config.orange_delay, ORANGE_COLOR);
                break;
            case PAUSE:
                DrawGame(screen, game, &animationTime);
                if (game.orangeTimer > 0)
                    DrawProgressBar(
                            screen, game.charset,
                            (SDL_Rect) {game.area.x - 8, game.area.y - 16, game.area.w + 16, 8},
                            game.orangeTimer, game.config.orange_delay, ORANGE_COLOR);
                pauseTime = SDL_GetTicks() - game.startTime - tickPrevious;
                break;
            case PAUSE_INFO:
                DrawGame(screen, game, &animationTime);
                if (game.orangeTimer > 0)
                    DrawProgressBar(
                            screen, game.charset,
                            (SDL_Rect) {game.area.x - 8, game.area.y - 16, game.area.w + 16, 8},
                            game.orangeTimer, game.config.orange_delay, ORANGE_COLOR);
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
