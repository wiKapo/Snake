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

part_t GetDirection(const point_t last, const point_t curr, const point_t next) {
    part_t snakePart = {BODY, NONE};
    if (last.x == -1)
        snakePart.type = HEAD;
    else if (next.x == -1)
        snakePart.type = TAIL;

    // Vertical movement
    if (last.x == curr.x && curr.x == next.x || (last.x == -1 && curr.x == next.x) ||
        (last.x == curr.x && next.x == -1)) {
        if ((last.y > curr.y && last.x != -1) || (next.y != -1 && curr.y > next.y))
            snakePart.direction = DOWN;
        else
            snakePart.direction = UP;
    }
        // Horizontal movement
    else if (last.y == curr.y && curr.y == next.y || (last.y == -1 && curr.y == next.y) ||
             (last.y == curr.y && next.y == -1)) {
        if ((curr.x < last.x && last.x != -1) || (curr.x > next.x && next.x != -1))
            snakePart.direction = RIGHT;
        else
            snakePart.direction = LEFT;
    }
        // Diagonal movement
    else if ((last.y == curr.y && curr.x == next.x) || (last.x == curr.x && curr.y == next.y)) {
        if (last.x > curr.x || next.x > curr.x) {// connects right
            if (curr.y < next.y || curr.y < last.y) // connects down
                snakePart.direction = RIGHTDOWN;
            else // connects up
                snakePart.direction = RIGHTUP;

        } else {// connects left
            if (curr.y < next.y || curr.y < last.y) // connects down
                snakePart.direction = LEFTDOWN;
            else // connects up
                snakePart.direction = LEFTUP;
        }
    }

    return snakePart;
}

void DrawSnake(SDL_Surface *screen, const point_t *pos, const int length, SDL_Surface *objects) {
    int px, py, c;
    SDL_Rect source, destination;
    source.w = 32;
    source.h = 32;
    destination.w = 32;
    destination.h = 32;

    for (int i = 0; i < length; i++) {
        part_t snakePart = GetDirection(
                i > 0 ? pos[i - 1] : (point_t) {-1, -1},
                pos[i],
                i < length - 1 ? pos[i + 1] : (point_t) {-1, -1});

        switch (snakePart.type) {
            case HEAD:
                source.y = 0;
                break;
            case BODY:
            default:
                if (snakePart.direction >= RIGHT && snakePart.direction <= UP)
                    source.y = i % 2 ? 32 : 64;
                else source.y = i % 2 ? 160 : 192;
                break;
            case TAIL:
                source.y = i % 2 ? 96 : 128;
        }

        switch (snakePart.direction) {
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
