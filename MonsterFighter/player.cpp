#include "player.h"
#include "globalVariables.h"

Player::Player() {
	mWidth = 10;
	mHeight = 10;
	mXpos = 10;
	mYpos = SCREEN_HEIGHT - mHeight;
	mPlayerBody = { mXpos,mYpos,mWidth,mHeight };
}

void Player::render() {
	//limit player movement
	if (mPlayerBody.x < 0) mPlayerBody.x = 0;
	if (mPlayerBody.x > SCREEN_WIDTH - mWidth) mPlayerBody.x = SCREEN_WIDTH - mWidth;
	if (mPlayerBody.y < 0) mPlayerBody.y = 0;
	if (mPlayerBody.y > SCREEN_HEIGHT - mHeight) mPlayerBody.y = SCREEN_HEIGHT - mHeight;
	//render players body
	SDL_SetRenderDrawColor(gRenderer,255,0,0,255);
	SDL_RenderFillRect(gRenderer,&mPlayerBody);
}


void Player::move(SDL_Event* e) {
	if (e->type == SDL_KEYDOWN) {
		switch (e->key.keysym.sym) {
		case SDLK_LEFT: mPlayerBody.x -= 5; break;
		case SDLK_RIGHT:mPlayerBody.x += 5; break;
		case SDLK_UP:mPlayerBody.y -= 5; break;
		case SDLK_DOWN:mPlayerBody.y += 5; break;
		}
	}
}

void Player::fixedCamera() {
	if (mPlayerBody.x + mPlayerBody.w > SCREEN_WIDTH && camera.x < LEVEL_WIDTH - camera.w) {
		camera.x += (LEVEL_WIDTH / X_LEVEL_LENGTH);
		mPlayerBody.x = 0;
	}

	if (mPlayerBody.x < 0 && camera.x > 0) {
		camera.x -= (LEVEL_WIDTH / X_LEVEL_LENGTH);
		mPlayerBody.x = SCREEN_WIDTH - mPlayerBody.w;
	}
}