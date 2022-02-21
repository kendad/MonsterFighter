#pragma once
#include <SDL.h>

class Player {
public:
	Player();
	void render();
	void move(SDL_Event* e);
	void fixedCamera();
private:
	SDL_Rect mPlayerBody;
	int mXpos;
	int mYpos;
	int mWidth;
	int mHeight;
};
