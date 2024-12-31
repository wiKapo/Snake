#ifndef STRUCTS_H
#define STRUCTS_H

#define DEBUG           1 //0 - false; 1 - true

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

typedef struct {
    direction_et direction;
    int change_direction;
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
    uint32_t startTime;
} game_t;

#endif