
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

static void render_court(void *obj, struct SDL_Renderer *renderer)
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
int main(int argc, char **argv)
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        return 1;
    }

    int quit;
    key_state = (Uint8 *)SDL_GetKeyboardState(NULL);

    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    window = make_window("Window");
    renderer = make_renderer(&window);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    set_up_timer();
    quit = 0;

    Ball *ball = ball_create("art/ball.png", renderer);
    Render_Q *render_q = render_q_create();
    Player *player_1 = player_create(renderer,
                                     100,                              // x
                                     ((WINDOW_HEIGHT / 2) - (32 / 2)), // y
                                     15,                               // width
                                     100, 0);                          // height
    Player *player_2 = player_create(renderer,
                                     WINDOW_WIDTH - (100 + 15),        // x
                                     ((WINDOW_HEIGHT / 2) - (32 / 2)), // y
                                     15,                               // width
                                     100, 0);                          // height
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

        ball->behavior(ball);
        ball->collision(ball, player_1);
        ball->collision(ball, player_2);
        player_1->player_1_bindings(player_1);
        player_1->player_2_bindings(player_2);
    }
    ball->destroy(ball);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
