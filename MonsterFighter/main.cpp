#include "basicFunctionalities.h"
#include "player.h"
#include "map.h"
#include "raycast.h"
#include "swing.h"
#include "playerAnimation.h"
#undef main

void main() {
	//Initialize the SDL
	if (!init()) {
		return;
	}

	bool isRunning = true;

	//Class Objects declared here
	Player player;
	Map map;
	Raycast raycast;
	Swing swing;
	PlayerAnimation playerAnimation;
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Assets/bg-1.png");

	//game Loop
	while (isRunning) {
		while (SDL_PollEvent(&userInputEvent) != 0) {
			if (userInputEvent.type == SDL_QUIT) isRunning = false;
			player.handelUserInput(&userInputEvent);
			swing.handelUserInput(&userInputEvent);
		}

		//clear the Renderer with a the COLOR
		SDL_SetRenderDrawColor(gRenderer,0,0,0,255);
		SDL_RenderClear(gRenderer);

		//draw stuff here
		//backgroundTexture.render(0, 0);
		//Obstacles
		map.renderObstacles();
		worldObstacles = map.getObstacles();
		//check for collision on the raycast and update the target position
		raycast.raycastToMousePosition(player.getPlayerRect(), map.getObstacles());
		//Swing and Player
		if (swing.isSwinging) swing.createSwing(&player, &raycast);
		if (swing.pointsVector.size() > 0) { swing.updatePlayerPositionSwing(&player); }
		player.move(map.getObstacles());

		swing.update();
		player.render();
		/*if (PLAYER_ANIMATION_TYPE == 2) {
			playerAnimation.playClimbAnimation(&player, true);
		}
		else
			if (swing.isSwinging && !swing.shouldPlayerJump) {
				if (!PLAYER_ANIMATION_FLIP) { playerAnimation.playStartSwingAnimation(&player); }
				else { playerAnimation.playStartSwingAnimation(&player, true); }
				swing.isSwinging = false;
			}
		else
			if (!swing.isSwinging && !swing.shouldPlayerJump) {
				if (!PLAYER_ANIMATION_FLIP) { playerAnimation.playSwingAnimation(&player); }
				else { playerAnimation.playSwingAnimation(&player, true); }
			}
		else
			if (!player.isGrounded) {
				if (!PLAYER_ANIMATION_FLIP) { playerAnimation.playJumpIdleAnimation(&player); }
				else { playerAnimation.playJumpIdleAnimation(&player, true); }
			}
		else {
				if (PLAYER_ANIMATION_TYPE == 1) { if (!PLAYER_ANIMATION_FLIP) { playerAnimation.playWalkAnimation(&player); } else { playerAnimation.playWalkAnimation(&player, true); } }
				if (PLAYER_ANIMATION_TYPE == 0) { if (!PLAYER_ANIMATION_FLIP) { playerAnimation.playIdleAnimation(&player); } else { playerAnimation.playIdleAnimation(&player, true); } }
			}*/

		//Update the Renderer with the new stuff
		SDL_RenderPresent(gRenderer);
	}
}