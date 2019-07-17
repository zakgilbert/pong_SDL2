
/************************
	 *  Ball.c
	*/

#include "Ball.h"
#include "Header.h"
#include "Window_and_Renderer.h"
#include "Player.h"

static int get_middle(struct SDL_Rect rect)
{
    return ((rect.x + (rect.w / 2)) + (rect.y + (rect.h / 2)));
}
static int get_intersection_left(struct SDL_Rect r1, struct SDL_Rect r2)
{
    int right_point = (get_middle(r1) - (r1.w / 2));
    int left_point = (get_middle(r2) + (r2.w / 2));
    return (right_point - left_point);
}
static int get_intersection_right(struct SDL_Rect r1, struct SDL_Rect r2)
{
    int right_point = (get_middle(r1) + (r1.w / 2));
    int left_point = (get_middle(r2) - (r2.w / 2));
    return (right_point - left_point);
}
static int ricochet(Ball *ball, Player *player)
{
    if (ball->vel_x > 0)
    {
        if (ball->vel_y < 0)
            ball->vel_y = abs(get_intersection_right(ball->rect, player->rect)) * -1;
        else
            ball->vel_y = abs(get_intersection_right(ball->rect, player->rect));
    }
    else
    {
        if (ball->vel_y < 0)
            ball->vel_y = abs(get_intersection_left(ball->rect, player->rect)) * -1;
        else
            ball->vel_y = abs(get_intersection_left(ball->rect, player->rect));
    }
    if (abs(ball->vel_y) > MAX_VELOCITY_Y)
        return MAX_VELOCITY_Y;
    return ball->vel_y;
}
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
        this->rect.x = WINDOW_WIDTH / 2;
        this->rect.y = 0;
    }
    else if (this->rect.y < -1 || this->rect.y > (WINDOW_HEIGHT - this->rect.h))
        this->vel_y *= -1;
    this->rect.x += this->vel_x;
    this->rect.y += this->vel_y;
}
static void _collision(Ball *this, Player *player)
{
    if (SDL_HasIntersection(&this->rect, &player->rect))
    {
        this->vel_x *= -1;
        this->vel_y = ricochet(this, player);
    }
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
    this->collision = _collision;

    this->vel_x = 16;
    this->vel_y = 8;

    this->texture = create_texture(renderer, path, &this->rect);
    return this;
}
