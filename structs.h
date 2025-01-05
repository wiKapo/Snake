#ifndef STRUCTS_H
#define STRUCTS_H

#define DEBUG           1 //0 - false; 1 - true

typedef struct {
    int width;
    int height;

    int start_speed;
    int start_length;
    int max_speed;

    int acceleration;
    int acceleration_interval;
    int apple_value;
    int orange_frequency;
    int orange_value;
    int slow_down;
    int portal_count;

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
    int speed;
} snake_t;

typedef struct {
    point_t *pos;
    int show;
} object_t;

typedef enum {
    QUIT = -1,
    INFO = 0,
    NEW_GAME = 1,
    PLAY = 2,
    GAME_OVER = 3,
    WIN = 4,
    PAUSE = 5,
    PAUSE_INFO = 6,
    LOAD = 7,
} state_et;

typedef enum {
    APPLE = 0,
    ORANGE = 1,
    PORTAL = 2,
} object_type_et;


typedef struct {
    config_t config;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Surface *charset;
    SDL_Surface *objectMap;
    SDL_Rect area;
    point_t *objectPos;
    state_et state;
    snake_t snake;
    object_t *object;
    uint32_t startTime;
    uint32_t deltaTime;
    int score;
} game_t;

#endif