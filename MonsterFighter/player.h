#pragma once
#include <SDL.h>
#include <vector>

class Player {
public:
	Player();
	void render();
	void handelUserInput(SDL_Event* e);
	void move(std::vector<SDL_Rect> obstacles);
	SDL_Rect getPlayerRect();
	SDL_Rect mPlayerBody;
private:
	int mXpos;
	int mYpos;

	int mWidth;
	int mHeight;

	int mVelX;
	int mVelY;

	int gravity;

	bool hasCollided;
	bool isGrounded;
};

