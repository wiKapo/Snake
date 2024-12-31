#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int width;
    int height;
} window_t;

typedef struct {
    window_t window;

    //game initialization
    float snake_speed;
    int snake_length;

    //game
    float acceleration;
    int apple_value;
    int orange_frequency;
    int orange_value;
    float slow_down;
    int fruit_mode;
} config_t;

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
    point_t *pos;
    int length;
} snake_t;

typedef struct {
    config_t config;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Surface *charset;
    SDL_Surface *objects;
    snake_t snake;
} game_t;

#endif