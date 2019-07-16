
/************************
	 *  Ball.c
	*/

#include "Ball.h"
#include "Header.h"
#include "Window_and_Renderer.h"

static void _destroy(Ball *this)
{
    if (NULL != this)
        free(this);

    this = NULL;
}

static void _behavior(Ball *this)
{
    if (this->rect.x < -1 || this->rect.x > (WINDOW_WIDTH - this->rect.w))
    {
        this->vel_x *= -1;
    }
    if (this->rect.y < -1 || this->rect.y > (WINDOW_HEIGHT - this->rect.h))
    {
        this->vel_y *= -1;
    }
    this->rect.x += this->vel_x;
    this->rect.y += this->vel_y;
}
static void _render(void *obj, struct SDL_Renderer *renderer)
{
    Ball *this = (Ball *)obj;

    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
}

Ball *ball_create(const char *path, struct SDL_Renderer *renderer)
{
    Ball *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->render = _render;
    this->behavior = _behavior;
    this->vel_x = 8;
    this->vel_y = 8;

    this->texture = create_texture(renderer, path, &this->rect);
    return this;
}
