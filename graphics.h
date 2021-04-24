#include <SDL.h>

// Below citation
typedef struct game_node {
    int x;
    int y;
} node;

static int initialiseDisplay();
int display (const struct World* initialState);
static int displayState (const int** state, const int rows, const int cols);
static void drawCell(node cell, SDL_Texture *stateTexture, int size);