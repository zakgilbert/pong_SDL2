
/************************
	 *  Ball.c   
     *  Contains all type defined functions for the ping pong ball        
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
    return (rect.y + (rect.h / 2));
}

/* Get the point from the middle of two rectangles intersection. */
static int get_intersection(struct SDL_Rect r1, struct SDL_Rect r2)
{
    int ball   = (get_middle_y(r1));
    int player = (get_middle_y(r2));

    return (ball - player);
}

/* Bounce the ball off a wall. */
static int ricochet(Ball* ball, Player* player, SDL_Rect* in)
{
    int neg = 1;
    if (ball->vel_y < 0) {
        neg = -1;
        ball->rect.y += in->h;
    } else {
        ball->rect.y -= in->h;
    }

    return ratio(abs(get_intersection(ball->rect, player->rect))) * neg;
}
/* Deallocate. */
static void _destroy(Ball* this)
{
    if (NULL != this)
        free(this);

    this = NULL;
}

/* Check where the ball should start after a point is scored. */
static void _behavior(Ball* this, Player* player_1, Player* player_2)
{
    if (this->rect.x < -1) {
        if (this->ball_in_play) {
            player_2->score++;
            this->ball_in_play = 0;
        }
        this->rect.x = WINDOW_WIDTH - 50;
        this->vel_x  = -this->start_vel_x;
        this->vel_y  = this->start_vel_y;
        if ((player_2->rect.y + (player_2->rect.h / 2)) > WINDOW_HEIGHT / 2)
            this->rect.y = 0;
        else
            this->rect.y = WINDOW_HEIGHT - 50;
    } else if (this->rect.x > (WINDOW_WIDTH)) {
        if (this->ball_in_play) {
            player_1->score++;
            this->ball_in_play = 0;
        }
        this->rect.x = 0;
        this->vel_x  = this->start_vel_x;
        this->vel_y  = this->start_vel_y;
        if ((player_1->rect.y + (player_1->rect.h / 2)) > WINDOW_HEIGHT / 2)
            this->rect.y = 0;
        else
            this->rect.y = WINDOW_HEIGHT - 50;
    } else if (this->rect.y < -1 || this->rect.y > (WINDOW_HEIGHT - this->rect.h)) {
        this->vel_y = -this->vel_y;
    }
    this->rect.x += this->vel_x;
    this->rect.y += this->vel_y;
}

/* Collided ball with a player. */
static void _collision(Ball* this, Player* player)
{
    SDL_Rect intersect;
    if (SDL_IntersectRect(&player->rect, &this->rect, &intersect)) {

        this->ball_in_play = 1;
        this->vel_x        = -this->vel_x;
        if (this->vel_x < 0) {
            this->vel_x--;
            this->rect.x -= intersect.w;
        } else if (this->vel_x >= 0) {
            this->vel_x++;
            this->rect.x += intersect.w * 2;
        }
        this->vel_y = ricochet(this, player, &intersect);
    }
}

/* Render ball image. */
static void _render(void* obj, struct SDL_Renderer* renderer)
{
    Ball* this = (Ball*)obj;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, &this->rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

/* Initialize the ball object. */
Ball* ball_create(const char* path, struct SDL_Renderer* renderer)
{
    Ball* this = malloc(sizeof(*this));

    this->destroy   = _destroy;
    this->render    = _render;
    this->behavior  = _behavior;
    this->collision = _collision;

    this->start_vel_x  = MIN_VELOCITY_X;
    this->start_vel_y  = MIN_VELOCITY_Y;
    this->vel_x        = this->start_vel_x;
    this->vel_y        = this->start_vel_y;
    this->ball_in_play = 0;
    this->rect.w       = BALL_SIZE;
    this->rect.h       = BALL_SIZE;

    return this;
}
