#include "player.h"
#include "globalVariables.h"
#include "basicFunctionalities.h"

Player::Player() {
	mWidth = 30;
	mHeight = 30;

	mXpos = 10;
	mYpos = 10;

	mPlayerBody = { mXpos,mYpos,mWidth,mHeight };

	mVelX = 0;
	mVelY = 0;

	gravity = 10;

	hasCollided = false;
	isGrounded = false;
}

void Player::render() {
	//render players body
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &mPlayerBody);
}


void Player::handelUserInput(SDL_Event* e) {
	if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
		switch (e->key.keysym.sym) {
		case SDLK_d:mVelX += 5; PLAYER_ANIMATION_TYPE = 1; PLAYER_ANIMATION_FLIP = false; break;
		case SDLK_a:mVelX -= 5; PLAYER_ANIMATION_TYPE = 1; PLAYER_ANIMATION_FLIP = true; break;
		case SDLK_SPACE: if (isGrounded) { gravity *= -1; mPlayerBody.y -= 1; isGrounded = false; } break;
		}
	}
	if (e->type == SDL_KEYUP && e->key.repeat == 0) {
		switch (e->key.keysym.sym) {
		case SDLK_d:mVelX -= 5; PLAYER_ANIMATION_TYPE = 0; break;
		case SDLK_a:mVelX += 5; PLAYER_ANIMATION_TYPE = 0; break;
		}
	}
}

void Player::move(std::vector<SDL_Rect> obstacles) {
	if (gravity < 10) { gravity++; }
	mPlayerBody.x += mVelX;
	mPlayerBody.y += mVelY;

	//check for general collision
	hasCollided = false;
	SDL_Rect obstacleCollided = SDL_Rect();
	for (int i = 0; i < obstacles.size(); i++) {
		if (checkCollision(mPlayerBody, obstacles[i])) { hasCollided = true; obstacleCollided = obstacles[i]; break; }
	}

	//check horizontal collision
	bool checkHorizontalCollision = mPlayerBody.y + mWidth<obstacleCollided.y + obstacleCollided.h && mPlayerBody.y>obstacleCollided.y;
	if (mPlayerBody.x < 0 || (mPlayerBody.x + mWidth > SCREEN_WIDTH) || (hasCollided && checkHorizontalCollision)) { mPlayerBody.x -= mVelX; }
	//check vertical collision
	if (mPlayerBody.y < 0 || (mPlayerBody.y + mHeight > SCREEN_HEIGHT) || hasCollided) { mVelY = 0; isGrounded = true; }
	else { mVelY = gravity; }
	//update Players y-axis
	if (mPlayerBody.y + mHeight > SCREEN_HEIGHT) { mPlayerBody.y = SCREEN_HEIGHT - mWidth; }
	if (mPlayerBody.y < 0) { mPlayerBody.y = 0; }
	if (hasCollided && (!checkHorizontalCollision) && mPlayerBody.y > obstacleCollided.y) { mPlayerBody.y = obstacleCollided.y + obstacleCollided.h; }
	if (hasCollided && (!checkHorizontalCollision) && mPlayerBody.y <= obstacleCollided.y) { mPlayerBody.y = obstacleCollided.y - mWidth; }
}

SDL_Rect Player::getPlayerRect() { return mPlayerBody; }