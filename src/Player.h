#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct _Player
{
    void (*render)(void *obj, struct SDL_Renderer *renderer);
    struct SDL_Rect rect;
} Player;
Player *player_create(struct SDL_Renderer *renderer);
#endif /* PLAYER_H */
