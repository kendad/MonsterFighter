#include "texture.h"
#include "globalVariables.h"
#include <iostream>

Texture::Texture() {
	mTexture = NULL;
	width = 0;
	height = 0;
}

void Texture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		width = 0;
		height = 0;
	}
}

//Texture::~Texture() {
//	free();
//}

void Texture::loadFromFile(std::string path) {
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	//set color key
	//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));

	//set new texture
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	//get width and height of the texture
	width = loadedSurface->w;
	height = loadedSurface->h;

	//free loaded surface
	SDL_FreeSurface(loadedSurface);

	//update texture
	mTexture = newTexture;
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x,y, width,height };
	if (clip != NULL) {
		renderQuad.w = 30;
		renderQuad.h = 30;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() { return width; }
int Texture::getHeight() { return height; }