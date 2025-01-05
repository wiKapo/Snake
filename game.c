#include "game.h"

void NewGame(game_t *game);

void QuickSave();

void QuickLoad(game_t *game);

void InitPlay(game_t *game);

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
                        if (game->state == PLAY || game->state == PAUSE) //maybe will delete pause option but idk
                            QuickSave();
                        break;
                    case SDLK_l:
                        QuickLoad(game);
                        break;
                    case SDLK_p:
                        if (game->state == PLAY || game->state == PAUSE_INFO)
                            game->state = PAUSE;
                        break;
                    case SDLK_h:
                        if (game->state == PLAY || game->state == PAUSE || game->state == PAUSE_INFO)
                            game->state = PAUSE_INFO;
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
                }
            default:
                break;
        }
    }
    if (snake->change_direction == 1) {
        if (game->state == NEW_GAME) InitPlay(game);
        else if (game->state == PAUSE || game->state == PAUSE_INFO) game->state = PLAY;
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
                    if (CheckSelfCollision(snake) || snake->pos[0].y == gameBoard.h / 32) {
                        snake->pos[0].y--; // Go back
                        snake->pos[0].y--; // Go left (here up)
                        if (CheckSelfCollision(snake) || snake->pos[0].y < 0) {
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
                    if (CheckSelfCollision(snake) || snake->pos[0].y < 0) {
                        snake->pos[0].y++; // Go back
                        snake->pos[0].y++; // Go left (here down)
                        if (CheckSelfCollision(snake) || snake->pos[0].y == gameBoard.h / 32) {
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
                    if (CheckSelfCollision(snake) || snake->pos[0].x < 0) {
                        snake->pos[0].x++; // Access denied
                        snake->pos[0].x++; // Turn left (sorry I meant right)
                        if (CheckSelfCollision(snake) || snake->pos[0].x == gameBoard.w / 32) {
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
                    if (CheckSelfCollision(snake) || snake->pos[0].x == gameBoard.w / 32) {
                        snake->pos[0].x--; // Go back
                        snake->pos[0].x--; // Go left (here left [HOW - Exyl])
                        if (CheckSelfCollision(snake) || snake->pos[0].x < 0) {
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

int CheckSelfCollision(snake_t *snake) {
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

void CheckFruitCollision(game_t *game) {
    snake_t *snake = &game->snake;
    if (snake->pos[0].x == game->objectPos[APPLE].x && snake->pos[0].y == game->objectPos[APPLE].y) {
        PlaceObject(game, APPLE);
        snake->length++;
        game->score += game->config.apple_value;
    } else if (snake->pos[0].x == game->objectPos[ORANGE].x && snake->pos[0].y == game->objectPos[ORANGE].y) {
        PlaceObject(snake, ORANGE);
        snake->length++;
        game->score += game->config.orange_value;
    }
}

void NewGame(game_t *game) {
    game->state = NEW_GAME;
    game->startTime = 0;
    game->deltaTime = 0;
    game->score = 0;
    game->snake.direction = UP;
    game->snake.speed = game->config.start_speed;
    game->snake.change_direction = 0;
    game->snake.length = game->config.start_length;
    for (int i = 0; i < game->snake.length; i++) {
        game->snake.pos[i].x = (game->area.w / 32 / 2) % 2 == 0 ? game->area.w / 32 / 2 - 1 : game->area.w / 32 / 2;
        game->snake.pos[i].y = game->area.h / 32 / 2 + i;
    }
    PlaceObject(game, APPLE);
}

void QuickSave() {}

void QuickLoad(game_t *game) {
    game->state = LOAD;
}

void InitPlay(game_t *game) {
    game->state = PLAY;
    game->startTime = SDL_GetTicks();
}

int CheckPosition(point_t *pos, int length, point_t newPos) {
    for (int i = 0; i < length; i++) {
        if (pos[i].x == newPos.x && pos[i].y == newPos.y)
            return 1;
    }
    return 0;
}

void PlaceObject(game_t *game, object_type_et type) {
    int object;
    if (type == APPLE || type == ORANGE) object = type;
    else
        for (int i = type; i < game->config.portal_count; i++)
            if (game->object[i].show == 0) object = i;

    point_t newPos = (point_t) {rand() % game->area.w / 32, rand() % game->area.h / 32};
    while (CheckPosition(game->objectPos, game->snake.length + game->config.portal_count + 2, newPos)) {
        newPos = newPos.x < game->area.w ? (point_t) {newPos.x++, newPos.y} :
                 newPos.y < game->area.h ? (point_t) {0, newPos.y++} : (point_t) {0, 0};
//        if (newPos.x < game->area.w) {
//            newPos = (point_t) {newPos.x++, newPos.y};
//        } else {
//            newPos = newPos.y < game->area.h ? (point_t) {0, newPos.y++} : (point_t) {0, 0};
//        }
    }

    game->objectPos[object] = newPos;
    game->object[object].show = 1;
}

char *GetStateKey(state_et state) {
    switch (state) {
        case QUIT:
            return "QUIT";
        case INFO:
            return "INFO";
        case NEW_GAME:
            return "NEW_GAME";
        case PLAY:
            return "PLAY";
        case GAME_OVER:
            return "GAME_OVER";
        case WIN:
            return "WIN";
        case PAUSE:
            return "PAUSE";
        case PAUSE_INFO:
            return "PAUSE_INFO";
        case LOAD:
            return "LOAD";
        default:
            return "UNKNOWN_STATE";
    }
}