#include <SDL.h>
#include "initSnake.h"
#include "game.h"
#include "draw.h"
#include "colors.h"
#include "time.h"

void DrawDebug(SDL_Surface *screen, game_t game);

void HandleNewScore(SDL_Surface *screen, game_t *game);

int main(int argc, char *argv[]) {
    game_t game = initGame();

    uint32_t tickPrevious = 0, pauseTime = 0;
    int delta = 0;

    SDL_Surface *screen = SDL_GetWindowSurface(game.window);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game.renderer, screen);

    while (game.state != QUIT) {
        FillScreen(screen, BROWN);

        DrawTopBar(screen, game.charset, game.clock.delta, game.state, game.score);
        DrawColorBox(screen, game.charset,
                     (SDL_Rect) {game.area.x - CHAR_SIZE, game.area.y - CHAR_SIZE,
                                 game.area.w + 2 * CHAR_SIZE, game.area.h + 2 * CHAR_SIZE}, 0, GRASS);

        if (DEBUG) DrawDebug(screen, game);

        HandleInput(&game);

        switch (game.state) {
            case INFO:
                DrawHelp(screen, game.charset);
                break;
            case NEW_GAME:
                DrawGame(screen, game, &game.clock.animation);
                ResetTime(&game.clock);
                pauseTime = tickPrevious = 0;
                game.inputState = NORMAL;
                break;
            case PLAY:
                UpdateTime(&game.clock, &delta, &tickPrevious, pauseTime, game.inputState);

                if (game.clock.orange < 0) {
                    game.clock.orange += delta;
                    if (game.clock.orange == 0)
                        if (rand() % 100 < game.config.orange_chance) {
                            PlaceObject(&game, ORANGE);
                            game.clock.orange = game.config.orange_delay;
                        } else game.clock.orange = -game.config.orange_delay / 2;
                } else if (game.clock.orange > 0) {
                    DrawProgressBar(screen, game.charset, game.area, game.clock.orange,
                                    game.config.orange_delay, ORANGE_COLOR);
                    game.clock.orange -= delta;
                    if (game.clock.orange == 0) {
                        RemoveObject(&game, ORANGE);
                        game.clock.orange = -game.config.orange_delay;
                    }
                }

                DrawGame(screen, game, &game.clock.animation);

                if (game.clock.acceleration > game.config.acceleration_interval &&
                    game.snake.speed > game.config.max_speed) {
                    game.snake.speed *= game.config.acceleration;
                    game.clock.acceleration -= game.config.acceleration_interval;
                } else if (game.snake.speed < game.config.max_speed) {
                    game.snake.speed = game.config.max_speed;
                }

                if (game.clock.move > game.snake.speed) {
                    game.clock.game += game.snake.speed;
                    game.clock.move -= game.snake.speed;

                    HandleMovement(&game.snake, game.area);

                    CheckFruitCollision(&game);
                    if (game.snake.length == game.config.width * game.config.height) game.state = WIN;
                    else if (CheckSelfCollision(&game.snake) || CheckBorderCollision(game.area, game.snake.pos[0]))
                        game.state = GAME_OVER;
                }
                break;
            case GAME_OVER:
            case WIN:
                UpdateTime(&game.clock, &delta, &tickPrevious, pauseTime, game.inputState);
                DrawGame(screen, game, &game.clock.animation);
                HandleNewScore(screen, &game);
                break;
            case LOAD:
                DrawGame(screen, game, &game.clock.animation);
                game.inputState = NORMAL;
                if (game.clock.orange > 0)
                    DrawProgressBar(screen, game.charset, game.area, game.clock.orange,
                                    game.config.orange_delay, ORANGE_COLOR);
                break;
            case PAUSE:
                DrawGame(screen, game, &game.clock.animation);
                if (game.clock.orange > 0)
                    DrawProgressBar(screen, game.charset, game.area, game.clock.orange,
                                    game.config.orange_delay, ORANGE_COLOR);
                pauseTime = SDL_GetTicks() - game.clock.start - game.clock.delta;
                break;
            case PAUSE_INFO:
                DrawGame(screen, game, &game.clock.animation);
                if (game.clock.orange > 0)
                    DrawProgressBar(screen, game.charset, game.area, game.clock.orange,
                                    game.config.orange_delay, ORANGE_COLOR);
                pauseTime = SDL_GetTicks() - game.clock.start - game.clock.delta;
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

#define BLINK_TIME 800  //milliseconds

void HandleNewScore(SDL_Surface *screen, game_t *game) {
    switch (game->inputState) {
        case NORMAL:
            if (game->score < game->highScores[2].score) {
                game->inputState = DONE;
                break;
            }
            sprintf(game->highScores[3].name, "");
            game->inputState = TEXT;

        case TEXT:
            const char *key = HandleKeyboard(&game->state);
            char *name = game->highScores[3].name;

            if (game->clock.animation < BLINK_TIME / 2)
                DrawInput(screen, game->charset, name, 0);
            else if (game->clock.animation < BLINK_TIME)
                DrawInput(screen, game->charset, name, 1);
            else game->clock.animation -= BLINK_TIME;

            if (HandleScoreInput(key, name)) {
                if (strlen(name) == 3) {
                    game->highScores[3].score = game->score;
                    UpdateScores(game->highScores);
                }
                game->inputState = DONE;
            }
            break;
        case DONE:
            if (game->state == GAME_OVER)
                DrawGameOver(screen, game->charset, game->score, game->clock.game);
            else if (game->state == WIN)
                DrawWin(screen, game->charset, game->score, game->clock.game);
            else
                DrawString(screen, game->charset, game->area.w / 2 - 15 * CHAR_SIZE, game->area.h / 2,
                           "HUH?! This should be impossible");
            DrawScores(screen, game->charset, game->highScores);
            break;
    }
}

void DrawDebug(SDL_Surface *screen, game_t game) {
    char text[100];
    //TOP DEBUG
    sprintf(text, "SNAKE: HEAD %02dx%02d SPEED %f MOVE TIME %d LENGTH %d",
            game.snake.pos->x, game.snake.pos->y, game.config.start_speed / (float) game.snake.speed,
            game.snake.speed, game.snake.length);
    DrawString(screen, game.charset, 10, 4.5 * CHAR_SIZE, text);

    sprintf(text, "GAME AREA %02dx%02d WINDOW SIZE %dx%d", game.config.width, game.config.height,
            screen->w, screen->h);
    DrawString(screen, game.charset, 10, 5.5 * CHAR_SIZE, text);

    sprintf(text, "INPUT STATE %s", GetInputStateKey(game.inputState));
    DrawString(screen, game.charset, 10, 6.5 * CHAR_SIZE, text);

    sprintf(text, "GAME STATE: %s", GetStateKey(game.state));
    DrawColorString(screen, game.charset, screen->w - (strlen(text) + 2) * CHAR_SIZE, 6.5 * CHAR_SIZE, text, YELLOW);

    //BOTTOM DEBUG
    sprintf(text, "GAME %u DELTA %u ANIMATION %u", game.clock.game, game.clock.delta, game.clock.animation);
    DrawString(screen, game.charset, 10, screen->h - 3.5 * CHAR_SIZE, text);

    if (game.clock.orange > 0)
        sprintf(text, "ORANGE TIMER %d ORANGE CHANCE %d ORANGE PROGRESS %.2f",
                game.clock.orange, game.config.orange_chance,
                game.clock.orange / (float) game.config.orange_delay);
    else sprintf(text, "ORANGE TIMER %d ORANGE CHANCE %d", game.clock.orange, game.config.orange_chance);
    DrawString(screen, game.charset, 10, screen->h - 2.5 * CHAR_SIZE, text);

    sprintf(text, "APPLE POS %02dx%02d ORANGE POS %02dx%02d",
            game.objectPos[APPLE].x, game.objectPos[APPLE].y,
            game.objectPos[ORANGE].x, game.objectPos[ORANGE].y);
    DrawString(screen, game.charset, 10, screen->h - 1.5 * CHAR_SIZE, text);
}