#include "globalVariables.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Event userInputEvent=SDL_Event();

SDL_Rect camera = {0,1440-480,SCREEN_WIDTH,SCREEN_HEIGHT};