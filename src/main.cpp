//Using SDL and standard IO
#include "std.h"
#include "SDL.h"
#include "SDL_image.h"
#include <cstdio>
#include "game/game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Surface* LoadSurface(SDL_Surface* pSurface, std::string path);

bool InitImagePng() {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        return false;
    }
    return true;
}

int SDL_main(int argc, char* args[]) {
    auto game = std::make_unique<Game>();
    game->Init("MyGame", SCREEN_WIDTH, SCREEN_HEIGHT);
    game->RunLoop();

    game = std::make_unique<Game>();
    game->Init("MyGame", SCREEN_WIDTH, SCREEN_HEIGHT);
    game->RunLoop();
    game = nullptr;

    //The window we'll be rendering to
    SDL_Window* window = nullptr;
    SDL_Renderer* gRenderer = nullptr;
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else if (!InitImagePng()) {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        } else {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);
            gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            auto sdlSurface = LoadSurface(screenSurface, "assets/Man.png");

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            SDL_Rect stretchRect{0, 0, 100, 100};
            SDL_BlitScaled(sdlSurface, NULL, screenSurface, &stretchRect);            //Update the surface

            SDL_UpdateWindowSurface(window);

            //Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while (quit == false) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) quit = true;
                    printf("...%d", e.type);
                }
            }
        }
    }

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}

SDL_Surface* LoadSurface(SDL_Surface* pSurface, std::string path) {
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, pSurface->format, 0);
        if (optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}