#include "basicFunctionalities.h"
#include "player.h"
#undef main

void main() {
	//Initialize the SDL
	if (!init()) {
		return;
	}

	bool isRunning = true;

	Texture sampleTexture;
	sampleTexture.loadFromFile("Assets/bg-2.png");
	Player samplePlayer;

	//game Loop
	while (isRunning) {
		while (SDL_PollEvent(&userInputEvent) != 0) {
			if (userInputEvent.type == SDL_QUIT) isRunning = false;
			samplePlayer.move(&userInputEvent);//handling players input
		}

		//clear the Renderer with a the COLOR
		SDL_SetRenderDrawColor(gRenderer,0,0,0,255);
		SDL_RenderClear(gRenderer);

		//draw stuff here
		//BG
		sampleTexture.render(0, 0,&camera);
		//player
		samplePlayer.fixedCamera();
		samplePlayer.render();

		//Update the Renderer with the new stuff
		SDL_RenderPresent(gRenderer);
	}
}