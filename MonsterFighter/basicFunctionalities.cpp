#include "basicFunctionalities.h"

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Could not INIT SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	gWindow = SDL_CreateWindow("Monster Fighter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gWindow == NULL) {
		std::cout << "Renderer Creation Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}

void handelUserInput(SDL_Event* e) {
	//For single Key Press
	if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
		switch (e->key.keysym.sym) {
		case SDLK_ESCAPE:std::cout << "testing ......" << std::endl; break;//testing__(delete later)
		}
	}
}

//#######################################################################################################################################################//
//#######################################################################################################################################################//

//TEXTURE CLASS
Texture::Texture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

void Texture::free() {
	if (mTexture != NULL) {
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

Texture::~Texture() {
	free();
}

void Texture::loadFromFile(std::string path) {
	free();
	SDL_Texture* newTexture;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	newTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);
	mTexture = newTexture;
}

void Texture::render(int x, int y, SDL_Rect* clip) {
	SDL_Rect destRect = { x,y,mWidth,mHeight };
	if (clip != NULL) {
		destRect.h = clip->h;
		destRect.w = clip->w;
	}
	SDL_RenderCopy(gRenderer,mTexture,clip,&destRect);
}

int Texture::getWidth() { return mWidth; }
int Texture::getHeight() { return mHeight; }

//#######################################################################################################################################################//
//#######################################################################################################################################################//

//Collision Detection
bool checkCollision(SDL_Rect a, SDL_Rect b) {
	//calculate the sides of the rectangle
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Rectangle A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Rectangle B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}