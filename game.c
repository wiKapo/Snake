#include "game.h"

void restartGame(game_t *game);

void quickSave();

void quickLoad();

void handleInput(game_t *game) {
    SDL_Event event;
    snake_t *snake = &game->snake;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        SDL_Quit();
                        exit(0);
                    case SDLK_n:
                        restartGame(game);
                        break;
                    case SDLK_s:
                        quickSave();
                        break;
                    case SDLK_l:
                        quickLoad();
                        break;
                    case SDLK_RIGHT:
                        if (snake->direction != LEFT && !snake->change_direction) {
                            snake->direction = RIGHT;
                            snake->change_direction = 1;
                        }
                        break;
                    case SDLK_DOWN:
                        if (snake->direction != UP && !snake->change_direction) {
                            snake->direction = DOWN;
                            snake->change_direction = 1;
                        }
                        break;
                    case SDLK_LEFT:
                        if (snake->direction != RIGHT && !snake->change_direction) {
                            snake->direction = LEFT;
                            snake->change_direction = 1;
                        }
                        break;
                    case SDLK_UP:
                        if (snake->direction != DOWN && !snake->change_direction) {
                            snake->direction = UP;
                            snake->change_direction = 1;
                        }
                        break;
                    case SDLK_p:
                        snake->direction = NONE;
                        break;
                }
            default:
                break;
        }
    }
    if (game->startTime == 0 && snake->direction != NONE)
        game->startTime = SDL_GetTicks();
}

void handleMovement(snake_t *snake) {
    if (snake->direction != NONE) {
        for (int i = snake->length - 1; i > 0; i--) {
            snake->pos[i] = snake->pos[i - 1];
        }
        snake->pos[0].x = snake->direction == RIGHT ? snake->pos[0].x + 1 :
                          snake->direction == LEFT ? snake->pos[0].x - 1 : snake->pos[0].x;
        snake->pos[0].y = snake->direction == DOWN ? snake->pos[0].y + 1 :
                          snake->direction == UP ? snake->pos[0].y - 1 : snake->pos[0].y;
    }
    snake->change_direction = 0;
}

void restartGame(game_t *game) {
    game->startTime = 0;
    game->snake.direction = NONE;
    game->snake.change_direction = 0;
    game->snake.length = 4;
    game->snake.pos[0] = (point_t) {10, 10};
    game->snake.pos[1] = (point_t) {10, 11};
    game->snake.pos[2] = (point_t) {10, 12};
    game->snake.pos[3] = (point_t) {10, 13};
}

void quickSave() {}

void quickLoad() {}