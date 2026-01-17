#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <cstdlib>
#include <string>

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"

constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

bool initialize_game();

void close_game();

/* Globals */
// Render window
SDL_Window* gWindow{nullptr};

// Window surface
SDL_Surface* gScreenSurface{nullptr};

int main(int argc, char* args[]) {
    if (not initialize_game()) {
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

    close_game();
    return EXIT_SUCCESS;
}

bool initialize_game() {
    if (not SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("Pong", kScreenWidth, kScreenHeight, 0);
    if (not gWindow) {
        SDL_Log("Error creating window. SDL error: %s\n", SDL_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

void close_game() {
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gScreenSurface = nullptr;

    SDL_Quit();
}