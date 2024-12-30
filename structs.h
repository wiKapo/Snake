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
    config_t config;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Surface *charset;
    SDL_Surface *objects;
} game_t;