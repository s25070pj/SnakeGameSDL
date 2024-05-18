#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>

using namespace std;

struct Segment {
    int x, y;
};

void renderSegment(SDL_Renderer* renderer, const Segment& segment) {
    SDL_Rect rect = {segment.x, segment.y, 20, 20};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}


void renderFood(SDL_Renderer* renderer, SDL_Rect food) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &food);
}

SDL_Rect createFood() {
    SDL_Rect food;
    food.w = 20;
    food.h = 20;
    food.x = (rand() % (640 / 20)) * 20;
    food.y = (rand() % (480 / 20)) * 20;
    return food;
}

bool checkCollision(const Segment& segment, const SDL_Rect& rect) {
    return segment.x == rect.x && segment.y == rect.y;
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


    // create snake and food
    vector<Segment> snake = {{100, 100}};
    SDL_Rect food = createFood();

    // rendering snake and food
    renderSegment(renderer, snake[0]);
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
            Segment newHead = {snake[0].x + directionX * speed, snake[0].y + directionY * speed};

            if (checkCollision(newHead, food)) {
                food = createFood();
            } else {
                snake.pop_back();
            }

            snake.insert(snake.begin(), newHead);

            SDL_SetRenderDrawColor(renderer, 0, 100, 10, 255);
            SDL_RenderClear(renderer);

            for (const auto& segment : snake) {
                renderSegment(renderer, segment);
            }
            renderFood(renderer, food);

            SDL_RenderPresent(renderer);
            lastMove = currentTime;
        }
    }

        // gc
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;


}