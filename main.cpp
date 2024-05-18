#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>

using namespace std;



void renderPlayer(SDL_Renderer* renderer, SDL_Rect player) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &player);
}

void renderFood(SDL_Renderer* renderer, SDL_Rect food) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &food);
}

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);

    //create window and renderer
    SDL_Window *window = SDL_CreateWindow("Snake",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640,
                                          480,
                                          SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window,
                                                -1,
                                                SDL_RENDERER_ACCELERATED
    );

    // color setting
    SDL_SetRenderDrawColor(renderer, 0, 100, 10, 255);
    SDL_RenderClear(renderer);

    // player creating
    SDL_Rect player;
    player.x = 100;
    player.y = 100;
    player.w = 20;
    player.h = 20;

    // food creating
    SDL_Rect food;
    food.x = 200;
    food.y = 200;
    food.w = 20;
    food.h = 20;

    // rendering player and food
    renderPlayer(renderer, player);
    renderFood(renderer, food);



    // presenting on the screen
    SDL_RenderPresent(renderer);

    //game
    bool quit = false;
    SDL_Event event;

    int directionX = 0;
    int directionY = 0;
    const int speed = 20;

    Uint32 lastMove = SDL_GetTicks();
    const Uint32 moveDelay = 100; // Move every 100 milliseconds

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        directionX = 0;
                        directionY = -1;
                        break;
                    case SDLK_s:
                        directionX = 0;
                        directionY = 1;
                        break;
                    case SDLK_a:
                        directionX = -1;
                        directionY = 0;
                        break;
                    case SDLK_d:
                        directionX = 1;
                        directionY = 0;
                        break;
                    default:
                        break;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastMove >= moveDelay) {
            player.x += directionX * speed;
            player.y += directionY * speed;
            lastMove = currentTime;

            SDL_SetRenderDrawColor(renderer, 0, 100, 10, 255);
            SDL_RenderClear(renderer);

            renderPlayer(renderer, player);
            renderFood(renderer, food);



            // presenting on the screen
            SDL_RenderPresent(renderer);
        }
    }

        // gc
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;


}