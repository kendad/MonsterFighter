#include "globalVariables.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Event userInputEvent=SDL_Event();

SDL_Rect camera = {0,1440-480,SCREEN_WIDTH,SCREEN_HEIGHT};

std::vector<SDL_Rect> worldObstacles = std::vector<SDL_Rect>();

int PLAYER_ANIMATION_TYPE = 0;
bool PLAYER_ANIMATION_FLIP = false;