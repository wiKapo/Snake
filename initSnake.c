#include "initSnake.h"

#define CONFIG_PATH     "../config.txt" //with cmake '../' is required

config_t read_config(char *path);

void initSDL(game_t *game);

void initAssets(game_t *game);

point_t testPos[19] = {
        {4, 2},
        {3, 2},
        {2, 2},
        {2, 3},
        {2, 4},
        {3, 4},
        {4, 4},
        {4, 5},
        {3, 5},
        {2, 5},
        {1, 5},
        {1, 6},
        {1, 7},
        {1, 8},
        {1, 9},
        {2, 9},
        {3, 9},
        {3, 8},
        {3, 7},
};

game_t initGame() {
    game_t game;

    game.config = read_config(CONFIG_PATH);
    if (DEBUG) {
        game.snake.pos = testPos;
        game.snake.length = sizeof(testPos) / sizeof(*testPos);
    } else {
        game.snake.pos = malloc(sizeof(point_t) * game.config.snake_length);
        game.snake.length = game.config.snake_length;
    }
    game.snake.direction = NONE;
    game.snake.change_direction = 0;
    game.startTime = 0;

    initSDL(&game);
    initAssets(&game);

    return game;
}

config_t read_config(char *path) {
    FILE *file = fopen(path, "r");
    config_t config = {{1280, 720}, 1, 3, 1, 1, 1, 5, 1, 1};
    if (file == NULL) {
        SDL_LogError(0, "Config not found!");
        return config;
    }

    while (!feof(file)) {
        char name[100];
        fscanf(file, "%s", name);
        if (!strcmp(name, "WINDOW_WIDTH"))
            fscanf(file, "%d", &config.window.width);
        else if (!strcmp(name, "WINDOW_HEIGHT"))
            fscanf(file, "%d", &config.window.height);
        else if (!strcmp(name, "START_SPEED"))
            fscanf(file, "%f", &config.snake_speed);
        else if (!strcmp(name, "START_LENGTH"))
            fscanf(file, "%d", &config.snake_length);
        else if (!strcmp(name, "APPLE_VALUE"))
            fscanf(file, "%d", &config.apple_value);
        else if (!strcmp(name, "ORANGE_FREQUENCY"))
            fscanf(file, "%d", &config.orange_frequency);
        else if (!strcmp(name, "ORANGE_VALUE"))
            fscanf(file, "%d", &config.orange_value);
        else if (!strcmp(name, "ACCELERATION"))
            fscanf(file, "%f", &config.acceleration);
        else if (!strcmp(name, "BONUS_SLOW_DOWN"))
            fscanf(file, "%f", &config.slow_down);
        else if (!strcmp(name, "FRUIT_MODE"))
            fscanf(file, "%d", &config.fruit_mode);
    }
    fclose(file);
    return config;
}

void initSDL(game_t *game) {
    config_t config = game->config;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(0, "SDL_Init error: %s\n", SDL_GetError());
        exit(1);
    }

    game->window = SDL_CreateWindow("Snake wiKapo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    config.window.width, config.window.height, SDL_WINDOW_SHOWN);

    if (!game->window) {
        SDL_LogError(0, "Failed to open %d x %d window: %s\n", config.window.width, config.window.height,
                     SDL_GetError());
        exit(1);
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);

    if (!game->renderer) {
        SDL_LogError(0, "Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void initAssets(game_t *game) {
    game->charset = SDL_LoadBMP("../assets/cs8x8.bmp");
    if (DEBUG)
        game->objects = SDL_LoadBMP("../assets/snakeDEBUG.bmp");
    else
        game->objects = SDL_LoadBMP("../assets/snake.bmp");


    if (!game->charset || !game->objects) {
        SDL_LogError(0, "Failed to load assets: %s\n", SDL_GetError());
        SDL_Quit();
        exit(99);
    }
}