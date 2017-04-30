#ifndef INIT_H
#define INIT_H
#include "textureWrapper.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool init();

bool load();

void clean();

void mainControl();
// For FPT controlling
void fps_init();

void fps_function();

// Error checking functions
bool errorCheck(SDL_Surface* surface);

bool errorCheck(SDL_Texture* texture);

bool errorCheck(SDL_Renderer* renderer);



#endif // INIT_H
