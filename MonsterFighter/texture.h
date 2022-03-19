#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture {
public:
	Texture();
	//~Texture();

	void loadFromFile(std::string path);
	void free();
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();
private:
	SDL_Texture* mTexture;
	int width;
	int height;
};
