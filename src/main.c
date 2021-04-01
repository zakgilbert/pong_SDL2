
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include "Header.h"
#include "Window_and_Renderer.h"
#include "Delta.h"
#include "Render_Q.h"
#include "Ball.h"
#include "Player.h"
#include "Atlas.h"
#include "Line.h"

 void render_court(void *obj, struct SDL_Renderer *renderer);
int main(int argc, char **argv)
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        return 1;
    }

    int quit;
    TURN = 1;
    key_state = (Uint8 *)SDL_GetKeyboardState(NULL);

    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    window = make_window("Window");
    renderer = make_renderer(&window);
    // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    // SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    set_up_timer();
    quit = 0;

    Ball *ball = ball_create("art/ball.png", renderer);
    Render_Q *render_q = render_q_create();
    Atlas *atlas = CREATE_ATLAS();
    atlas->map(atlas, renderer);

    Player *player_1 = player_create(renderer,
                                     100,
                                     ((WINDOW_HEIGHT / 2) - (32 / 2)));

    Player *player_2 = player_create(renderer,
                                     WINDOW_WIDTH - (100 + 15),
                                     ((WINDOW_HEIGHT / 2) - (32 / 2)));
    ball->rect.x = WINDOW_WIDTH / 2;
    ball->rect.y = 0;
    union SDL_Event ev;
    while (!quit)
    {
        start_timer();
        render_q->enqueue(render_q, render_q->create_node(ball, ball->render));
        render_q->enqueue(render_q, render_q->create_node(player_1, player_1->render));
        render_q->enqueue(render_q, render_q->create_node(player_2, player_2->render));
        render_q->enqueue(render_q, render_q->create_node(NULL, render_court));
        render_q->enqueue(render_q, render_q->create_node( CREATE_LINE(atlas, player_1->get_score(player_1), 250, 50), render_line0));
        render_q->enqueue(render_q, render_q->create_node( CREATE_LINE(atlas, player_2->get_score(player_2), WINDOW_WIDTH - 275, 50), render_line0));

        SDL_RenderClear(renderer);
        render_q = render_q->execute(render_q, renderer);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&ev) != 0)
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                quit = 1;
                break;
            }
        }
        ball->behavior(ball, player_1, player_2);
        ball->collision(ball, player_1);
        ball->collision(ball, player_2);
        player_1->player_bindings(player_1, W, S);
        player_2->player_bindings(player_2, UP, DOWN);

        delay();
        reset_timer();
    }
    ball->destroy(ball);
    atlas->destroy(atlas);
    player_1->destroy(player_1);
    player_2->destroy(player_2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

 void render_court(void *obj, struct SDL_Renderer *renderer)
{
    struct SDL_Rect rect;
    rect.w = 6;
    rect.h = 30;
    rect.x = (WINDOW_WIDTH / 2) - (rect.w / 2);
    rect.y = 0;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    while (rect.y + rect.h <= WINDOW_HEIGHT)
    {
        SDL_RenderFillRect(renderer, &rect);
        rect.y += rect.h + 10;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}