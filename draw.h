#include <SDL.h>
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

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);

void DrawTime(SDL_Surface *screen, int x, int y, char *text, SDL_Surface *charset);

void DrawSnake(SDL_Surface *screen, const point_t *pos, int length, SDL_Surface *objects);

void DrawObject(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *objects);

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);

void TestPrint(SDL_Surface *screen, SDL_Surface *objects);

#endif //SNAKEWKP_DRAW_H
