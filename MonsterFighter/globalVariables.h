#pragma once
#include <SDL.h>
#include <vector>

//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

//TOP DOWN approach //MAP
extern int worldMatrix[SCREEN_WIDTH / 10][SCREEN_HEIGHT / 10];

const int X_LEVEL_LENGTH=4;

const int LEVEL_WIDTH = SCREEN_WIDTH * X_LEVEL_LENGTH;
const int LEVEL_HEIGHT = SCREEN_HEIGHT;

struct vec2D
{
	int x;
	int y;
};

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern SDL_Event userInputEvent;

extern SDL_Rect camera;

extern std::vector<SDL_Rect> worldObstacles;

extern int PLAYER_ANIMATION_TYPE;
extern bool PLAYER_ANIMATION_FLIP;