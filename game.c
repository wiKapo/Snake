#include "game.h"

void NewGame(game_t *game);

void QuickSave();

void QuickLoad(game_t *game);

void initPlay(game_t *game);

void HandleInput(game_t *game) {
    SDL_Event event;
    snake_t *snake = &game->snake;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game->state = QUIT;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        game->state = QUIT;
                        break;
                    case SDLK_n:
                        NewGame(game);
                        break;
                    case SDLK_s:
                        QuickSave();
                        break;
                    case SDLK_l:
                        QuickLoad(game);
                        break;
                    case SDLK_h:
                        if (game->state == PLAY)
                            game->state = PAUSE;
                        else
                            game->state = INFO;
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
                        game->state = PAUSE;
                        break;
                }
            default:
                break;
        }
    }
    if (snake->change_direction == 1) {
        if (game->state == NEW_GAME) initPlay(game);
        else if (game->state == PAUSE) game->state = PLAY;
    }
}

void HandleMovement(snake_t *snake, SDL_Rect gameBoard) {
    if (snake->direction != NONE) {
        for (int i = snake->length - 1; i > 0; i--) {
            snake->pos[i] = snake->pos[i - 1];
        }
//        SIMPLE MOVEMENT
//        snake->pos[0].x = snake->direction == RIGHT ? snake->pos[0].x + 1 :
//                          snake->direction == LEFT ? snake->pos[0].x - 1 : snake->pos[0].x;
//        snake->pos[0].y = snake->direction == DOWN ? snake->pos[0].y + 1 :
//                          snake->direction == UP ? snake->pos[0].y - 1 : snake->pos[0].y;
        switch (snake->direction) {
            case RIGHT:
                if (snake->pos[0].x < gameBoard.w / 32 - 1)
                    snake->pos[0].x++;
                else { // Going outside the game board on the right
                    // try to turn because project
                    snake->pos[0].y++; // Go right (here down)
                    if (CheckCollision(snake) || snake->pos[0].y == gameBoard.h / 32) {
                        snake->pos[0].y--; // Go back
                        snake->pos[0].y--; // Go left (here up)
                        if (CheckCollision(snake) || snake->pos[0].y < 0) {
                            snake->pos[0].y++; // Go back again
                            snake->pos[0].x++; // Get stuck in the wall >:)
                        } else {
                            snake->direction = UP;
                        }
                    } else
                        snake->direction = DOWN;
                }
                break;
            case LEFT:
                if (snake->pos[0].x > 0)
                    snake->pos[0].x--;
                else { // Going outside the game board on the left
                    // try to turn because project
                    snake->pos[0].y--; // Go right (here up)
                    if (CheckCollision(snake) || snake->pos[0].y < 0) {
                        snake->pos[0].y++; // Go back
                        snake->pos[0].y++; // Go left (here down)
                        if (CheckCollision(snake) || snake->pos[0].y == gameBoard.h / 32) {
                            snake->pos[0].y--; // Go back again
                            snake->pos[0].x--; // Go back to the wall and die :)
                        } else {
                            snake->direction = DOWN;
                        }
                    } else {
                        snake->direction = UP;
                    }
                }
                break;
            case DOWN:
                if (snake->pos[0].y < gameBoard.h / 32 - 1)
                    snake->pos[0].y++;
                else { // Going outside the game board on the top
                    // try to turn because project
                    snake->pos[0].x--; // Turn right (sorry I meant left)
                    if (CheckCollision(snake) || snake->pos[0].x < 0) {
                        snake->pos[0].x++; // Access denied
                        snake->pos[0].x++; // Turn left (sorry I meant right)
                        if (CheckCollision(snake) || snake->pos[0].x == gameBoard.w / 32) {
                            snake->pos[0].x--; // Access denied
                            snake->pos[0].y++; // Give up
                        } else {
                            snake->direction = RIGHT;
                        }
                    } else {
                        snake->direction = LEFT;
                    }
                }
                break;
            case UP:
                if (snake->pos[0].y > 0)
                    snake->pos[0].y--;
                else { // Going outside the game board on the bottom
                    // try to turn because project
                    snake->pos[0].x++; // Go right (here right [IMPOSSIBLE])
                    if (CheckCollision(snake) || snake->pos[0].x == gameBoard.w / 32) {
                        snake->pos[0].x--; // Go back
                        snake->pos[0].x--; // Go left (here left [HOW - Exyl])
                        if (CheckCollision(snake) || snake->pos[0].x < 0) {
                            snake->pos[0].x++; // Why are we still here?
                            snake->pos[0].y--; // Just to suffer?
                        } else {
                            snake->direction = LEFT;
                        }
                    } else {
                        snake->direction = RIGHT;
                    }
                }
                break;
            default:
                break;
        }
    }
    snake->change_direction = 0;
}

int CheckCollision(snake_t *snake) {
    for (int i = 1; i < snake->length; i++) {
        if (snake->pos[0].x == snake->pos[i].x && snake->pos[0].y == snake->pos[i].y) {
            snake->direction = NONE;
            return 1;
        }
    }
    return 0;
}

int CheckBorderCollision(SDL_Rect gameBoard, point_t snakeHead) {
    if (snakeHead.x < 0 || snakeHead.x >= gameBoard.w / 32 || snakeHead.y < 0 || snakeHead.y >= gameBoard.h / 32)
        return 1;
    return 0;
}

void NewGame(game_t *game) {
    game->state = NEW_GAME;
    game->startTime = 0;
    game->deltaTime = 0;
    game->score = 0;
    game->snake.direction = UP;
    game->snake.change_direction = 0;
    game->snake.length = game->config.snake_length;
    for (int i = 0; i < game->snake.length; i++) {
        game->snake.pos[i].x = game->config.window.width / 32 / 2;
        game->snake.pos[i].y = game->config.window.height / 32 / 2 + i;
    }
}

void QuickSave() {}

void QuickLoad(game_t *game) {
    game->state = LOAD;
}

void initPlay(game_t *game) {
    game->state = PLAY;
    game->startTime = SDL_GetTicks();
}