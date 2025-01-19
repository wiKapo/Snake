#include <SDL.h>
#include "structs.h"
#include "file.h"

#ifndef SNAKEWKP_GAME_H
#define SNAKEWKP_GAME_H

void HandleInput(game_t *game);

void HandleMovement(snake_t *snake, SDL_Rect gameBoard);

void HandlePortals(snake_t *snake, point_t *portalPos, int portal_count);

const char *HandleKeyboard(state_et *state);

int HandleScoreInput(const char *key, char name[3 + 1]);

int CheckSelfCollision(snake_t *snake);

int CheckBorderCollision(SDL_Rect gameBoard, point_t snakeHead);

void CheckFruitCollision(game_t *game);

void PlaceObject(game_t *game, object_type_et type);

void RemoveObject(game_t *game, object_type_et type);

char *GetStateKey(state_et state);

char *GetInputStateKey(input_et state);

void GetAutoDirection(point_t *objects, snake_t *snake, int tryNum);

#endif //SNAKEWKP_GAME_H
