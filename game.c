#include "game.h"

#define NOTIFICATION_TIME   1000    // milliseconds

void NewGame(game_t *game);

void QuickSave(game_t *game);

void QuickLoad(game_t *game);

void InitPlay(game_t *game);

void HandleInput(game_t *game) {
    if (game->inputState == TEXT) return;

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
                        if (game->state == PLAY || game->state == PAUSE || game->state == PAUSE_INFO)
                            QuickSave(game);
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
        if (game->state == NEW_GAME || game->state == LOAD) InitPlay(game);
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

const char *HandleKeyboard(state_et *state) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *state = QUIT;
                return "";
            case SDL_KEYDOWN:
                const char *key = SDL_GetKeyName(event.key.keysym.sym);
                int keycode = SDL_GetKeyFromName(key);
                if (keycode >= 'a' && keycode <= 'z' || keycode >= '0' && keycode <= '9' || keycode == SDLK_ESCAPE ||
                    keycode == SDLK_BACKSPACE || keycode == SDLK_RETURN)
                    return key;
                return "";
        }
    }
    return "";
};

int HandleScoreInput(const char *key, char name[3 + 1]) {
    int length = strlen(name);
    if (!strcmp(key, "Backspace")) {
        if (length > 0)
            name[length - 1] = '\0';
    } else if (!strcmp(key, "Return") && length == 3)
        return 1;
    else if (!strcmp(key, "Escape")) {
        name[0] = '\0';
        return 1;
    } else if (length < 3 && strlen(key) && strcmp(key, "Return") != 0)
        strcat(name, key);

    if (strcmp(key, "") && DEBUG) SDL_LogInfo(0, "PRESSED: %s NAME: %s", key, name);
    return 0;
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
    if (snake->pos[0].x == game->object[APPLE].pos->x && snake->pos[0].y == game->object[APPLE].pos->y) {
        PlaceObject(game, APPLE);
        snake->length++;
        game->score += game->config.apple_value;
    } else if (snake->pos[0].x == game->object[ORANGE].pos->x && snake->pos[0].y == game->object[ORANGE].pos->y) {
        RemoveObject(game, ORANGE);
        game->score += game->config.orange_value;
        game->clock.orange = -game->config.orange_delay;
        if (rand() % 100 < 50) {
            if (snake->length - game->config.bonus_shorten < game->config.start_length) {
                for (int i = game->config.start_length; i < snake->length; i++)
                    snake->pos[i] = (point_t) {NULL_POS, NULL_POS};
                snake->length = game->config.start_length;
            } else {
                for (int i = snake->length - game->config.bonus_shorten; i < snake->length; i++)
                    snake->pos[i] = (point_t) {NULL_POS, NULL_POS};
                snake->length -= game->config.bonus_shorten;
            }
        } else snake->speed *= game->config.bonus_slow_down;
    }
}

void NewGame(game_t *game) {
    game->state = NEW_GAME;
    game->score = 0;

    game->snake.direction = UP;
    game->snake.speed = game->config.start_speed;
    game->snake.change_direction = 0;
    //Clear snake positions
    for (int i = game->config.start_length; i < game->snake.length; i++)
        game->snake.pos[i] = (point_t) {NULL_POS, NULL_POS};

    game->snake.length = game->config.start_length;
    for (int i = 0; i < game->snake.length; i++)
        game->snake.pos[i] = (point_t) {
                (game->area.w / 32 / 2) % 2 == 0 ? game->area.w / 32 / 2 - 1 : game->area.w / 32 / 2,
                game->area.h / 32 / 2 + i};

    game->clock.start = 0;
    game->clock.game = 0;
    game->clock.orange = -game->config.orange_delay;

    PlaceObject(game, APPLE);
    PlaceObject(game, PORTAL);
    RemoveObject(game, ORANGE);
}

void QuickSave(game_t *game) {
    game->clock.notification = NOTIFICATION_TIME;
    SaveGame(*game);
}

void QuickLoad(game_t *game) {
    LoadGame(game);
}

void InitPlay(game_t *game) {
    game->state = PLAY;
    game->clock.start = SDL_GetTicks();
}

int CheckPosition(point_t *pos, int length, point_t newPos) {
    for (int i = 0; i < length; i++) {
        if (pos[i].x == newPos.x && pos[i].y == newPos.y)
            return 1;
    }
    return 0;
}

void DoPlace(game_t *game, int object) {
    point_t newPos = (point_t) {rand() % game->config.width, rand() % game->config.height};
    while (CheckPosition(game->objectPos, game->snake.length + 2 + game->config.portal_count * 2, newPos)) {
        newPos = newPos.x < game->config.width - 1 ? (point_t) {++newPos.x, newPos.y} :
                 newPos.y < game->config.height - 1 ? (point_t) {0, ++newPos.y} : (point_t) {0, 0};
    }

    *game->object[object].pos = newPos;
    game->object[object].show = 1;
}

void PlaceObject(game_t *game, object_type_et type) {
    if (type == APPLE || type == ORANGE)
        DoPlace(game, type);
    else
        for (int i = type; i < 2 + game->config.portal_count * 2; i += 2)
            if (i / 2 * 40 < game->config.width * game->config.height) {
                DoPlace(game, i);
                DoPlace(game, i + 1);
            }
}

void DoRemove(game_t *game, int object) {
    *game->object[object].pos = (point_t) {NULL_POS, NULL_POS};
    game->object[object].show = 0;
}

void RemoveObject(game_t *game, object_type_et type) {
    if (type == APPLE || type == ORANGE) DoRemove(game, type);
    else
        for (int i = type; i < game->config.portal_count; i++)
            if (game->object[i].show == 1) DoRemove(game, i);
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

char *GetInputStateKey(input_et state) {
    switch (state) {
        case NORMAL:
            return "NORMAL";
        case TEXT:
            return "TEXT";
        case DONE:
            return "DONE";
    }
}