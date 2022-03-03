#pragma once
#include "player.h"
#include "swing.h"
#include "texture.h"

//create OBJECT after world INITILIZATION

class PlayerAnimation {
public:
	PlayerAnimation();
	void playIdleAnimation(Player* player, bool flip = false);
	void playWalkAnimation(Player* player, bool flip = false);
	void playStartSwingAnimation(Player* player, bool flip = false);
	void playSwingAnimation(Player* player, bool flip = false);
	void playClimbAnimation(Player* player, bool flip = false);

	void playJumpStartAnimation(Player* player, bool flip = false);
	void playJumpIdleAnimation(Player* player, bool flip = false);
	void playJumpEndAnimation(Player* player, bool flip = false);
private:
	//Player Texture
	Texture playerTexture;

	//Idle Position
	int idleFrame;
	int idleTime;
	SDL_Rect IdlePositionClip[3];

	//Walk Animation
	int walkFrame;
	int walkTime;
	SDL_Rect WalkClip[6];

	//Swing Start Animation
	int swingStartFrame;
	int swingStartTime;
	SDL_Rect SwingStartClip[3];

	//Swing Animation
	SDL_Rect SwingClip[1];

	//Climb Animation
	SDL_Rect ClimbClip[1];

	//Jump Animation
	int jumpStartFrame;
	int jumpEndFrame;
	int jumpStartTime;
	int jumpEndTime;
	SDL_Rect JumpStartClip[3];
	SDL_Rect JumpIdleClip;
	SDL_Rect JumpEndClip[2];
};