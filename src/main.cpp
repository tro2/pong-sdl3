#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <cstdlib>

#include "gameConstants.h"

bool initializeGame();

void closeGame();

/* Globals */
// Render window
SDL_Window* gWindow{nullptr};

// Window surface
SDL_Surface* gScreenSurface{nullptr};

int main(int argc, char* args[]) {
    SDL_Log("Application launched.\n");

    if (not initializeGame()) {
        SDL_Log("Unable to initialize game!\n");
        return EXIT_FAILURE;
    }

    // quit flag
    bool quit{false};

    // Current event data
    SDL_Event currEvent;
    SDL_zero(currEvent);

    // main loop
    while (not quit) {
        while (SDL_PollEvent(&currEvent)) {
            if (currEvent.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            // Make surface white
            SDL_FillSurfaceRect(
                gScreenSurface, nullptr,
                SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));

            SDL_UpdateWindowSurface(gWindow);
        }
    }

    closeGame();
    return EXIT_SUCCESS;
}

bool initializeGame() {
    SDL_Log("Application initializing...\n");

    if (not SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("Pong", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (not gWindow) {
        SDL_Log("Error creating window. SDL error: %s\n", SDL_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    SDL_Log("Application initialized!\n");
    return true;
}

void closeGame() {
    SDL_Log("Application closing.\n");

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gScreenSurface = nullptr;

    SDL_Quit();
}