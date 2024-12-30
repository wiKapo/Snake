#include <SDL.h>

typedef struct {
    int x;
    int y;
} point_t;

typedef enum {
    NONE = -1,
    RIGHT = 0,
    DOWN = 1,
    LEFT = 2,
    UP = 3,
    LEFTUP = 4,
    LEFTDOWN = 5,
    RIGHTDOWN = 6,
    RIGHTUP = 7,
} direction_et;

typedef enum {
    HEAD = 0,
    BODY = 1,
    TAIL = 2,
} snake_type_et;

typedef struct {
    snake_type_et type;
    direction_et direction;
} snake_t;

#ifndef SNAKEWKP_DRAW_H
#define SNAKEWKP_DRAW_H

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);

void DrawSnake(SDL_Surface *screen, const point_t *pos, int posLength, SDL_Surface *objects);

void DrawObject(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *objects);

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);

void TestPrint(SDL_Surface *screen, SDL_Surface *objects);

#endif //SNAKEWKP_DRAW_H
