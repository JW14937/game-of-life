#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "logic.h"
#include "graphics.h"

SDL_Renderer* renderer = NULL;

SDL_Surface*  live_cell_surface = NULL;
SDL_Surface*  dead_cell_surface = NULL;

SDL_Texture*  live_cell_texture = NULL;
SDL_Texture*  dead_cell_texture = NULL;


/** Initialise the graphical display using SDL
 * Return 0 if successful, 1 otherwise */
static int initialiseDisplay()
{
    // Attribute the code?
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initialising SDL: %s\n", SDL_GetError()); 
        return 1;
    }
    atexit(SDL_Quit);

    SDL_Window *window = NULL;

    SDL_CreateWindowAndRenderer(500, 500, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Game of Life");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    live_cell_surface = SDL_LoadBMP("images/live_cell.bmp");
    dead_cell_surface = SDL_LoadBMP("images/dead_cell.bmp");

    live_cell_texture = SDL_CreateTextureFromSurface(renderer, live_cell_surface);
    dead_cell_texture = SDL_CreateTextureFromSurface(renderer, dead_cell_surface);

    return 0;
}

/** Entry point for displaying the evolutionary process graphically
 * Takes in struct to initial state of the world and displays the cells as squares
 * Listens for user input - either right-arrow key or Esc
 * If right-arrow key is pressed, displays the next evolutionary step
 * If Esc is pressed, exits the program
 * Exits with code 0 if successful, returns 1 otherwise */
int display(const struct World* initialState) {

    initialiseDisplay();

    // Display the initial state
    displayState(initialState->state, initialState->rows, initialState->columns);

    // Load the next generation

    int** nextStateArray = (int**)malloc(initialState->rows * sizeof(int*));
    for(int i=0; i<initialState->columns; i++) { 
        nextStateArray[i] = (int*)malloc(initialState->columns * sizeof(int)); 
    }
    nextStateArray = nextState(initialState->state, initialState->rows, initialState->columns);

    // Iterate through generations

    for(int i=0; i<initialState->nrOfGenerations; i++) {

        SDL_Event e;
        
        while(SDL_WaitEvent(&e) != 0) {
            
            // Exit if user closed the window or pressed Esc
            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) { exit(0); }
            
            // Display the next generation if user pressed the right-arrow key

            else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT) {

                displayState(nextStateArray, initialState->rows, initialState->columns);

                // Create a buffer copy
                int** bufferArray = (int**)malloc(initialState->rows * sizeof(int*));
                for(int i=0; i<initialState->rows; i++) {

                    bufferArray[i] = (int*)malloc(initialState->columns * sizeof(int));

                    for(int j=0; j<initialState->columns; j++) {
                        bufferArray[i][j] = nextStateArray[i][j];
                    }
                }

                // Free the previous state
                for(int i=0; i<initialState->rows; i++) { free(nextStateArray[i]); }
                free(nextStateArray);

                // Load the next state using the buffer copy
                nextStateArray = nextState(bufferArray, initialState->rows, initialState->columns);

                // Free the buffer
                for(int i=0; i<initialState->rows; i++) { free(bufferArray[i]); }
                free(bufferArray);

                // Proceed to the next generation
                continue;
            }
        }
    }
    return 0;
}

/** Takes in a pointer to 2D array representing a state of the world
 * Displays it graphically
 * Returns 0 if successful, 1 otherwise */
static int displayState (const int** state, const int rows, const int cols) {
    
    node cells[rows][cols];

    // Determine the size of a drawn cell, depending on their number
    int cellSize;
    if(rows >= cols) { cellSize = 500/rows; }
    else { cellSize = 500/cols; }

    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {

            cells[i][j].x = j;
            cells[i][j].y = i;
            
            // Live cell
            if(state[i][j] == 1) { drawCell(cells[i][j], live_cell_texture, cellSize); }

            // Dead cell
            else if(state[i][j] == 0) { drawCell(cells[i][j], dead_cell_texture, cellSize); }

            // Error - state must be 1 or 0
            else { return 1; }
        }
    }

    SDL_RenderPresent(renderer);

    return 0;
}

// Citation ?
void drawCell(node cell, SDL_Texture *stateTexture, int size) {

    SDL_Rect drawnCell;

    drawnCell.w = size;
    drawnCell.h = size;

    drawnCell.x = cell.x * size;
    drawnCell.y = cell.y * size;

    SDL_RenderCopy(renderer, stateTexture, NULL, &drawnCell);

    return;
}