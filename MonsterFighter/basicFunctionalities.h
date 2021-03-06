#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "globalVariables.h"

bool init();//intializes SDL 

void close();//Closes everything when application closes

void handelUserInput(SDL_Event* e);//handel User Inputs#pragma once

bool checkCollision(SDL_Rect a, SDL_Rect b);//check for collision between two objects(AABB)

//draw the grid world on the screen
void drawGridWorld();
vec2D convertScreenToGridSpace(int x, int y);
vec2D convertGridSpaceToScreenSpace(int x, int y);

//LERP
float lerp(float normal, float min, float max);