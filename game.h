#include <SDL.h>
#include "structs.h"

#ifndef SNAKEWKP_GAME_H
#define SNAKEWKP_GAME_H

void HandleInput(game_t *game);

void HandleMovement(snake_t *snake, SDL_Rect gameBoard);

int CheckCollision(snake_t *snake);

int CheckBorderCollision(SDL_Rect gameBoard, point_t snakeHead);

#endif //SNAKEWKP_GAME_H
