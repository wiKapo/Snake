#include "draw.h"

void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset) {
    int px, py, c;
    SDL_Rect source, destination;
    source.w = 8;
    source.h = 8;
    destination.w = 8;
    destination.h = 8;
    while (*text) {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        source.x = px;
        source.y = py;
        destination.x = x;
        destination.y = y;
        SDL_BlitSurface(charset, &source, screen, &destination);
        x += 8;
        text++;
    }
}

snake_t GetDirection(const point_t last, const point_t curr, const point_t next) {
    snake_t snakeDir = {BODY, NONE};
    if (last.x == -1)
        snakeDir.type = HEAD;
    else if (next.x == -1)
        snakeDir.type = TAIL;

    // Vertical movement
    if (last.x == curr.x && curr.x == next.x || (last.x == -1 && curr.x == next.x) ||
        (last.x == curr.x && next.x == -1)) {
        if ((last.y > curr.y && last.x != -1) || (next.y != -1 && curr.y > next.y))
            snakeDir.direction = DOWN;
        else
            snakeDir.direction = UP;
    }
        // Horizontal movement
    else if (last.y == curr.y && curr.y == next.y || (last.y == -1 && curr.y == next.y) ||
             (last.y == curr.y && next.y == -1)) {
        if (last.x > curr.x)
            snakeDir.direction = RIGHT;
        else
            snakeDir.direction = LEFT;
    }
        // Diagonal movement
    else if ((last.y == curr.y && curr.x == next.x) || (last.x == curr.x && curr.y == next.y)) {
        if (last.x > curr.x || next.x > curr.x) {// connects right
            if (curr.y < next.y || curr.y < last.y) // connects down
                snakeDir.direction = RIGHTDOWN;
            else // connects up
                snakeDir.direction = RIGHTUP;

        } else {// connects left
            if (curr.y < next.y || curr.y < last.y) // connects down
                snakeDir.direction = LEFTDOWN;
            else // connects up
                snakeDir.direction = LEFTUP;
        }
    }

    return snakeDir;
}

void DrawSnake(SDL_Surface *screen, const point_t *pos, const int posLength, SDL_Surface *objects) {
    int px, py, c;
    SDL_Rect source, destination;
    source.w = 32;
    source.h = 32;
    destination.w = 32;
    destination.h = 32;

    for (int i = 0; i < posLength; i++) {
        //GET DIRECTION
//        if (pos[i].y == pos[i - 1].y) {
//            if (pos[i].x > pos[i - 1].x)
//                source.x = 64;      // LEFT
//            else if (pos[i].x < pos[i - 1].x)
//                source.x = 0;       // RIGHT
//        } else {
//            if (pos[i].y > pos[i - 1].y)
//                source.x = 32;      //DOWN
//            else if (pos[i].y < pos[i - 1].y)
//                source.x = 96;      //UP
//            else source.x = 112;
//        }
//        SDL_LogInfo(0, "ITERATION %d", i);
        snake_t snakeDir = GetDirection(
                i > 0 ? pos[i - 1] : (point_t) {-1, -1},
                pos[i],
                i < posLength - 1 ? pos[i + 1] : (point_t) {-1, -1});
        switch (snakeDir.type) {
            case HEAD:
                source.y = 0;
                break;
            case BODY:
            default:
                if (snakeDir.direction >= RIGHT && snakeDir.direction <= UP)
                    source.y = i % 2 ? 32 : 64;
                else source.y = i % 2 ? 160 : 192;
                break;
            case TAIL:
                source.y = i % 2 ? 96 : 128;
        }

        switch (snakeDir.direction) {
            case RIGHT:
            case LEFTUP:
                source.x = 0;
                break;
            case DOWN:
            case LEFTDOWN:
                source.x = 32;
                break;
            case LEFT:
            case RIGHTDOWN:
                source.x = 64;
                break;
            case UP:
            case RIGHTUP:
                source.x = 96;
                break;
            case NONE:
            default:
                source.x = 224;
                source.y = 224;
                break;
        }

        destination.x = pos[i].x * 32;
        destination.y = pos[i].y * 32;
        SDL_BlitSurface(objects, &source, screen, &destination);
    }
}

//void DrawObject(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *objects) {
//    int px, py, c;
//    SDL_Rect source, destination;
//    source.w = 32;
//    source.h = 32;
//    destination.w = 32;
//    destination.h = 32;
//    while (*text) {
//        c = *text & 255;
//        px = (c % 8) * 32;
//        py = (c / 8) * 32;
//        source.x = px;
//        source.y = py;
//        destination.x = x;
//        destination.y = y;
//        SDL_BlitSurface(objects, &source, screen, &destination);
//        x += 32;
//        text++;
//    };
//};

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
    SDL_Rect dest;
    dest.x = x - sprite->w / 2;
    dest.y = y - sprite->h / 2;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, screen, &dest);
};

void TestPrint(SDL_Surface *screen, SDL_Surface *objects) {
    SDL_Rect source, destination;
    source.w = 32;
    source.h = 32;
    destination.w = 32;
    destination.h = 32;
    source.x = 0;
    source.y = 0;
    destination.x = 100;
    destination.y = 100;
    SDL_BlitSurface(objects, &source, screen, &destination);
}
