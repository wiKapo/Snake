#include <SDL.h>
#include <stdio.h>
#include "structs.h"

#ifndef SNAKEWKP_DRAW_H
#define SNAKEWKP_DRAW_H

typedef enum {
    HEAD = 0,
    BODY = 1,
    TAIL = 2,
} part_type_et;

typedef struct {
    part_type_et type;
    direction_et direction;
} part_t;

void DrawTopBar(SDL_Surface *screen, SDL_Surface *charset, uint32_t deltaTime, state_et state, int score);

void DrawGameOver(SDL_Surface *screen, SDL_Surface *charset, int score, int time);

void DrawWin(SDL_Surface *screen, SDL_Surface *charset, int score, int time);

void DrawHelp(SDL_Surface *screen, SDL_Surface *charset);

void DrawBox(SDL_Surface *screen, SDL_Surface *charset, SDL_Rect rect, int type);

void DrawColorBox(SDL_Surface *screen, SDL_Surface *charset, SDL_Rect rect, int type, uint32_t color);

void DrawString(SDL_Surface *screen, SDL_Surface *charset, int x, int y, const char *text);

void DrawColorString(SDL_Surface *screen, SDL_Surface *charset, int x, int y, const char *text, SDL_Color color);

void DrawTime(SDL_Surface *screen, SDL_Surface *charset, int x, int y, uint32_t time);

void DrawColorTime(SDL_Surface *screen, SDL_Surface *charset, int x, int y, uint32_t time, SDL_Color color);

void DrawSnake(SDL_Surface *screen, SDL_Surface *objects, SDL_Rect gameArea, const point_t *pos, int length);

void DrawObjects(SDL_Surface *screen, SDL_Surface *charset, SDL_Rect gameArea, const point_t *pos, int length);

void DrawGame(SDL_Surface *screen, game_t game);

#endif //SNAKEWKP_DRAW_H
