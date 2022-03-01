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

class Texture {
public:
	Texture();
	~Texture();

	void loadFromFile(std::string path);
	void free();
	void render(int x,int y,SDL_Rect* clip=NULL);

	int getWidth();
	int getHeight();
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};