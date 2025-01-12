#include "initSnake.h"

#define CONFIG_PATH     "../config.txt" //with cmake '../' is required

void initSDL(game_t *game);

void initAssets(game_t *game);

game_t initGame() {
    game_t game;
    game.config = GetConfig(CONFIG_PATH);

    int objectCount = game.config.width * game.config.height * OBJECT_SIZE;
    game.objectPos = malloc(sizeof(point_t) * objectCount);
    for (int i = 0; i < objectCount; i++)
        game.objectPos[i] = (point_t) {NULL_POS, NULL_POS};

    game.snake.pos = &game.objectPos[2 + game.config.portal_count];
    game.snake.length = game.config.start_length;
    game.snake.direction = UP;
    game.snake.speed = game.config.start_speed;
    game.snake.change_direction = 0;

    game.clock.orange = -game.config.orange_delay;
    game.clock.start = 0;
    game.clock.game = 0;

    game.area = (SDL_Rect) {1.5 * OBJECT_SIZE, 2.25 * OBJECT_SIZE, game.config.width * OBJECT_SIZE,
                            game.config.height * OBJECT_SIZE};
    game.object = malloc(sizeof(object_t) * (game.config.portal_count + 2));
    for (int i = 0; i < game.config.portal_count; i++) {
        game.object[i].pos = &game.objectPos[i];
        game.object[i].show = 0;
    }

    game.state = INFO;
    game.inputState = NORMAL;

    game.score = 0;
    game.highScores = GetScores();

    initSDL(&game);
    initAssets(&game);

    return game;
}

void initSDL(game_t *game) {
    config_t config = game->config;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(0, "SDL_Init error: %s\n", SDL_GetError());
        exit(1);
    }

    int width = 600, height = 600;
    if (config.width * OBJECT_SIZE > 600)
        width = config.width * OBJECT_SIZE + 3 * OBJECT_SIZE;
    if (config.height * OBJECT_SIZE + 40 > 600)
        height = config.height * OBJECT_SIZE + 3 * OBJECT_SIZE + 18;

    game->window = SDL_CreateWindow("Snake wiKapo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    width, height, SDL_WINDOW_SHOWN);

    if (!game->window) {
        SDL_LogError(0, "Failed to open %d x %d window: %s\n", config.width, config.height,
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
        game->objectMap = SDL_LoadBMP("../assets/snakeDEBUG.bmp");
    else
        game->objectMap = SDL_LoadBMP("../assets/snake.bmp");


    if (!game->charset || !game->objectMap) {
        SDL_LogError(0, "Failed to load assets: %s\n", SDL_GetError());
        SDL_Quit();
        exit(99);
    }
}