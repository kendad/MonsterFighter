#include "basicFunctionalities.h"
#include "player.h"
#include "map.h"
#include "raycast.h"
#include "swing.h"
#undef main

void main() {
	//Initialize the SDL
	if (!init()) {
		return;
	}

	bool isRunning = true;

	//Class Objects declared here
	Player player;
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Assets/bg-2.png");
	Map map;
	Raycast raycast;
	Swing swing;

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
		//Background Image
		backgroundTexture.render(0, 0,&camera);
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

		//Update the Renderer with the new stuff
		SDL_RenderPresent(gRenderer);
	}
}