#include <SDL.h>

using namespace std;


int main(int argc, char* argv[]) {

    SDL_Init( SDL_INIT_EVERYTHING );
    auto window = SDL_CreateWindow( "Okienko SDL",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    640, 480,
                                    SDL_WINDOW_SHOWN );
    SDL_Delay(2000);
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;

}