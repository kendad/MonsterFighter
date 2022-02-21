#pragma once
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int X_LEVEL_LENGTH=4;

const int LEVEL_WIDTH = SCREEN_WIDTH * X_LEVEL_LENGTH;
const int LEVEL_HEIGHT = SCREEN_HEIGHT;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern SDL_Event userInputEvent;

extern SDL_Rect camera;
