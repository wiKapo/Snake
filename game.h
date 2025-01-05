#include <SDL.h>
#include "structs.h"

#ifndef SNAKEWKP_GAME_H
#define SNAKEWKP_GAME_H

void HandleInput(game_t *game);

void HandleMovement(snake_t *snake, SDL_Rect gameBoard);

int CheckSelfCollision(snake_t *snake);

int CheckBorderCollision(SDL_Rect gameBoard, point_t snakeHead);

void CheckFruitCollision(game_t *game);

void PlaceObject(game_t *game, object_type_et type);

char *GetStateKey(state_et state);

#endif //SNAKEWKP_GAME_H
