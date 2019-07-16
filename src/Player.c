
/************************
	 *  Player.c
	*/

#include "Player.h"
#include "Header.h"

static void _render(void *obj, struct SDL_Renderer *renderer)
{
    Player *this = (Player *)obj;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}
Player *player_create(struct SDL_Renderer *renderer)
{
    Player *this = malloc(sizeof(*this));
    this->render = _render;

    this->rect.w = 15;
    this->rect.h = 30;
    this->rect.x = 10;
    this->rect.y = (WINDOW_HEIGHT / 2) - (this->rect.h / 2);

    return this;
}