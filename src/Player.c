
/************************
	 *  Player.c
	*/

#include "Player.h"
#include "Header.h"
#include "Ball.h"
#include "Rectangle_Functions.h"

int confirm_keystate(int key_val)
{
    if (!key_state[key_val])
        return 0;
    return 1;
}

static void _render(void *obj, struct SDL_Renderer *renderer)
{
    Player *this = (Player *)obj;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

static void _player_bindings(Player *this, int up, int down)
{
    if (confirm_keystate(up) && this->rect.y > 0)
        this->rect.y -= this->vel;
    else if (confirm_keystate(down) && get_bottom(this->rect) < WINDOW_HEIGHT)
        this->rect.y += this->vel;
}

Player *player_create(struct SDL_Renderer *renderer, int x, int y, int w, int h, int player)
{
    Player *this = malloc(sizeof(*this));
    this->render = _render;
    this->player_bindings = _player_bindings;

    this->rect.w = w;
    this->rect.h = h;
    this->rect.x = x;
    this->rect.y = y;

    this->vel = 20;

    this->player = player;

    return this;
}