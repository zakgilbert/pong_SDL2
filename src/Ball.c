
/************************
	 *  Ball.c           
	*/

#include "Ball.h"
#include "Header.h"
#include "Window_and_Renderer.h"
#include "Player.h"

static int ratio(int value)
{
    int y = MAX_VELOCITY_Y * value;
    return y / 100;
}

static int get_middle_y(struct SDL_Rect rect)
{
    // printf("topY: %d\nbottomY: %d\nmiddle: %d\n", rect.y, rect.y + rect.w, (rect.y + (rect.h / 2)));
    return (rect.y + (rect.h / 2));
}
static int get_intersection_left(struct SDL_Rect r1, struct SDL_Rect r2)
{
    int ball = (get_middle_y(r1));
    int player = (get_middle_y(r2));
    // printf("Player 2 intersected this ball at %d\n    where the paddle was at %d\n            diff is %d\n", ball, player, (ball - player));
    return (ball - player);
}
static int get_intersection_right(struct SDL_Rect r1, struct SDL_Rect r2)
{
    int ball = (get_middle_y(r1));
    int player = (get_middle_y(r2));
    // printf("Player 1 intersected this ball at %d\n    where the paddle was at %d\n            diff is %d\n", ball, player, (ball - player));
    return (ball - player);
}
static int ricochet(Ball *ball, Player *player)
{
    int neg = 1;
    if (ball->vel_y < 0)
        neg = -1;

    return ball->vel_y = ratio(abs(get_intersection_right(ball->rect, player->rect))) * neg;
}
static void _destroy(Ball *this)
{
    if (NULL != this)
        free(this);

    this = NULL;
}

static void _behavior(Ball *this, Player *player_1, Player *player_2)
{
    if (this->rect.x < -1)
    {
        player_2->score++;
        this->rect.x = WINDOW_WIDTH - 50;
        this->vel_x = this->start_vel_x * -1;
        this->vel_y = this->start_vel_y;
        if ((player_2->rect.y + (player_2->rect.h / 2)) > WINDOW_HEIGHT / 2)
            this->rect.y = 0;
        else
            this->rect.y = WINDOW_HEIGHT - 50;
    }
    else if (this->rect.x > (WINDOW_WIDTH))
    {
        player_1->score++;
        this->rect.x = 0;
        this->vel_x = this->start_vel_x;
        this->vel_y = this->start_vel_y;
        if ((player_1->rect.y + (player_1->rect.h / 2)) > WINDOW_HEIGHT / 2)
            this->rect.y = 0;
        else
            this->rect.y = WINDOW_HEIGHT - 50;
    }
    else if (this->rect.y < -1 || this->rect.y > (WINDOW_HEIGHT - this->rect.h))
    {
        this->vel_y *= -1;
    }
    this->rect.x += this->vel_x;
    this->rect.y += this->vel_y;
}
static void _collision(Ball *this, Player *player)
{
    if (SDL_HasIntersection(&this->rect, &player->rect))
    {
        this->vel_x *= -1;
        if (this->vel_x < 0)
            this->vel_x--;
        else
            this->vel_x++;

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
    this->start_vel_x = 16;
    this->start_vel_y = 8;
    this->vel_x = this->start_vel_x;
    this->vel_y = this->start_vel_y;

    this->texture = create_texture(renderer, path, &this->rect);
    return this;
}
