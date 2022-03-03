#include "playerAnimation.h"
#include "globalVariables.h"
#include <iostream>

PlayerAnimation::PlayerAnimation() {
	//load the files
	playerTexture.loadFromFile("Assets/spiderman.png");

	//IDLE ANIMATION
	idleFrame = 0;
	idleTime = SDL_GetTicks();
	IdlePositionClip[0] = { 13,43,50,56 };
	IdlePositionClip[1] = { 75,41,45,59 };
	IdlePositionClip[2] = { 134,45,41,54 };

	//WALK ANIMATION
	walkFrame = 0;
	walkTime = SDL_GetTicks();
	WalkClip[0] = { 10,127,43,63 };
	WalkClip[1] = { 68,127,39,65 };
	WalkClip[2] = { 130,130,39,65 };
	WalkClip[3] = { 190,128,37,65 };
	WalkClip[4] = { 244,129,39,63 };
	WalkClip[5] = { 297,130,50,63 };

	//SWING START ANIMATION
	swingStartFrame = 0;
	swingStartTime = SDL_GetTicks();
	SwingStartClip[0] = { 312,360,42,61 };
	SwingStartClip[1] = { 374,345,43,78 };
	SwingStartClip[2] = { 440,348,39,72 };

	//SWING ANIMATION
	SwingClip[0] = { 493,362,39,49 };

	//CLIMB ANIMATION
	ClimbClip[0] = { 553,359,40,55 };

	//JUMP ANIMATION
	jumpStartFrame = 0;
	jumpStartTime = SDL_GetTicks();
	jumpEndFrame = 0;
	jumpEndTime = SDL_GetTicks();
	JumpStartClip[0] = { 194,45,42,51 };
	JumpStartClip[1] = { 244,31,44,71 };
	JumpStartClip[2] = { 298,1,43,96 };
	JumpIdleClip = { 194,45,42,51 };
	JumpEndClip[0] = { 362,63,39,33 };
	JumpEndClip[1] = { 414,60,60,41 };
}

void PlayerAnimation::playIdleAnimation(Player* player, bool flip) {
	if (flip == false) {
		playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &IdlePositionClip[idleFrame]);
	}
	else { playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &IdlePositionClip[idleFrame], 180, NULL, SDL_FLIP_VERTICAL); }
	if (SDL_GetTicks() - idleTime >= 130) {
		idleFrame++;
		if (idleFrame >= 3)idleFrame = 0;
		idleTime = SDL_GetTicks();
	}
}

void PlayerAnimation::playWalkAnimation(Player* player, bool flip) {
	if (flip == false) {
		playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &WalkClip[walkFrame]);
	}
	else { playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &WalkClip[walkFrame], 180, NULL, SDL_FLIP_VERTICAL); }
	if (SDL_GetTicks() - walkTime >= 130) {
		walkFrame++;
		if (walkFrame >= 6)walkFrame = 0;
		walkTime = SDL_GetTicks();
	}
}

void PlayerAnimation::playStartSwingAnimation(Player* player, bool flip) {
	if (flip == false) {
		playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &SwingStartClip[swingStartFrame]);
	}
	else { playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &SwingStartClip[swingStartFrame], 180, NULL, SDL_FLIP_VERTICAL); }
	if (SDL_GetTicks() - swingStartTime >= 130) {
		swingStartFrame++;
		if (swingStartFrame >= 3)swingStartFrame = 0;
		swingStartTime = SDL_GetTicks();
	}
}

void PlayerAnimation::playSwingAnimation(Player* player, bool flip) {
	if (flip == false) {
		playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &SwingClip[0]);
	}
	else { playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &SwingClip[0], 180, NULL, SDL_FLIP_VERTICAL); }
}

void PlayerAnimation::playClimbAnimation(Player* player, bool flip) {
	if (flip == false) {
		playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &ClimbClip[0]);
	}
	else { playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &ClimbClip[0], 180, NULL, SDL_FLIP_VERTICAL); }
}

void PlayerAnimation::playJumpIdleAnimation(Player* player, bool flip) {
	if (flip == false) {
		playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &JumpIdleClip);
	}
	else { playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &JumpIdleClip, 180, NULL, SDL_FLIP_VERTICAL); }
}

void PlayerAnimation::playJumpStartAnimation(Player* player, bool flip) {
	if (flip == false) {
		playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &JumpStartClip[jumpStartFrame]);
	}
	else { playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &JumpStartClip[jumpStartFrame], 180, NULL, SDL_FLIP_VERTICAL); }
	if (SDL_GetTicks() - jumpStartTime >= 200) {
		jumpStartFrame++;
		if (jumpStartFrame >= 3)jumpStartFrame = 0;
		jumpStartTime = SDL_GetTicks();
	}
}

void PlayerAnimation::playJumpEndAnimation(Player* player, bool flip) {
	if (flip == false) {
		playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &JumpEndClip[jumpEndFrame]);
	}
	else { playerTexture.render(player->getPlayerRect().x, player->getPlayerRect().y, &JumpEndClip[jumpEndFrame], 180, NULL, SDL_FLIP_VERTICAL); }
	if (SDL_GetTicks() - jumpEndTime >= 130) {
		jumpEndFrame++;
		if (jumpEndFrame >= 2)jumpEndFrame = 0;
		jumpEndTime = SDL_GetTicks();
	}
}