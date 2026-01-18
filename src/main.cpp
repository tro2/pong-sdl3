#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <cstdlib>

#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_render.h"
#include "gameConstants.hpp"
#include "gameRect.hpp"

bool initializeGame();

void closeGame();

/* Globals */
// Render window
SDL_Window* gameWindow{nullptr};

// Window surface
SDL_Renderer* gameRenderer{nullptr};

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

    // Display box
    GameRect box{{0, 0, 100, 100}, {0, 0, 0, 255}};

    // main loop
    while (not quit) {
        while (SDL_PollEvent(&currEvent)) {
            if (currEvent.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            // Fill the background white
            SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gameRenderer);

            // Draw box
            const auto [r, g, b, a] = box.getColor();
            SDL_SetRenderDrawColor(gameRenderer, r, g, b, a);
            SDL_RenderRect(gameRenderer, &box.getRect());
            SDL_RenderFillRect(gameRenderer, &box.getRect());

            // Update screen
            SDL_RenderPresent(gameRenderer);
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

    if (not SDL_CreateWindowAndRenderer("Pong", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &gameWindow, &gameRenderer)) {
        SDL_Log("Error creating window and renderer. SDL error: %s\n", SDL_GetError());
        return false;
    }

    SDL_Log("Application initialized!\n");
    return true;
}

void closeGame() {
    SDL_Log("Application closing.\n");

    SDL_DestroyRenderer(gameRenderer);
    gameRenderer = nullptr;
    SDL_DestroyWindow(gameWindow);
    gameWindow = nullptr;

    SDL_Quit();
}