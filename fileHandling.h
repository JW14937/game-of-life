#include <stdio.h>

const struct World* loadInitialState (const char* filename, const char* generationsString, const char* rowsString, const char* columnsString);
int saveFinalState (const struct World* finalState, const char* filename);
int onlyDigits (const char* text);

// make onlyNumbers static if it works with unity