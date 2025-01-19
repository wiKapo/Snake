#ifndef STRUCTS_H
#define STRUCTS_H

#define DEBUG                       0   //0 - false; 1 - true; 2 - detailed
#define NULL_POS                    (-99)
#define OBJECT_SIZE                 32  //pixels
#define CHAR_SIZE                   8   //pixels
#define MAX_SMALL_BOARD_POS_W       15  //positions
#define MAX_SMALL_BOARD_POS_H       7   //positions
#define MAX_SMALL_BOARD_WIDTH       (MAX_SMALL_BOARD_POS_W * OBJECT_SIZE) //pixels
#define MAX_SMALL_BOARD_HEIGHT      (MAX_SMALL_BOARD_POS_H * OBJECT_SIZE) //pixels
#define MIN_WINDOW_WIDTH            (MAX_SMALL_BOARD_WIDTH + 3 * OBJECT_SIZE) //pixels
#define MIN_WINDOW_HEIGHT           (MAX_SMALL_BOARD_HEIGHT + 3 * OBJECT_SIZE + 2 * CHAR_SIZE) //pixels

typedef struct {
    //game board width
    int width;
    //game board height
    int height;

    int start_speed;
    int start_length;
    int max_speed;

    float acceleration;
    int acceleration_interval;

    //points for fruits
    int apple_value;
    int orange_value;

    //orange related
    int orange_delay;
    int orange_chance;
    float bonus_slow_down;
    int bonus_shorten;

    int portal_count;
    //decides what textures to use
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
    char *name;
    int score;
} score_t;

typedef enum {
    NORMAL = 0,
    TEXT = 1,
    DONE = 2,
} input_et;

typedef struct {
    uint32_t start;
    uint32_t game;
    uint32_t delta;
    uint32_t animation;
    uint32_t acceleration;
    uint32_t move;
    int orange;
    int notification;
} clock_t;

typedef struct {
    config_t config;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Surface *charset;
    SDL_Surface *objectMap;

    SDL_Rect area;
    point_t *objectPos;
    snake_t snake;
    object_t *object;

    state_et state;
    input_et inputState;

    clock_t clock;

    int score;
    score_t *highScores;

    int automatic;
} game_t;

#endif