#ifndef BALL_H
#define BALL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct _Ball
{
    void (*destroy)(struct _Ball *this);
    void (*render)(void *obj, struct SDL_Renderer *renderer);
    void (*behavior)(struct _Ball *this);
    struct SDL_Texture *texture;
    struct SDL_Rect rect;

    int vel_x;
    int vel_y;

} Ball;

Ball *ball_create(const char *path, struct SDL_Renderer *renderer);

#endif /* BALL_H */
