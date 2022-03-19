#include "basicFunctionalities.h"
#include "player.h"
#include "map.h"
#include "raycast.h"
#include "swing.h"
#include "playerAnimation.h"
#include "astar.h"
#include "IK.h"
#include "spider.h"
#include "boid.h"
#undef main

void main() {
	//Initialize the SDL
	if (!init()) {
		return;
	}

	bool isRunning = true;

	//Class Objects declared here
	Player player;
	Spider spider;
	Map map;
	Raycast raycast;
	Swing swing;
	PlayerAnimation playerAnimation;
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Assets/bg-1.png");

	//Astar Initilization
	vec2D startPos = { 0,0 };
	vec2D endPos = { 99,79 };
	Node startNode = Node(startPos);
	Node endNode = Node(endPos);
	Astar astar = Astar(&startNode, &endNode);
	astar.update();

	//Inverse Kinematics
	vec2D startPoint = { SCREEN_WIDTH / 2 - 100,SCREEN_HEIGHT / 2 };
	vec2D controlPoint = { SCREEN_WIDTH / 2 - 100,SCREEN_HEIGHT / 2 };
	InverseKinematics ik = InverseKinematics(10,40,&startPoint,&controlPoint);

	//Boids Initilization
	std::vector<Boid> boids;
	for (int i = 0; i < 100; i++) {
		Boid tmpBoid = Boid((SCREEN_WIDTH / 2) - 100, SCREEN_HEIGHT / 2);
		//Boid tmpBoid = Boid(rand()%(0,SCREEN_WIDTH-1), rand() % (0, SCREEN_HEIGHT - 1));
		boids.push_back(tmpBoid);
	}
	int x, y;
	Vector target = Vector(0, 0);

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
		backgroundTexture.render(0, 0);
		//Obstacles
		//map.renderObstacles();
		//worldObstacles = map.getObstacles();
		//drawGridWorld();
		
		//Astar Visulizer
		/*vec2D tmpVec = { player.getPlayerRect().x / 10,player.getPlayerRect().y / 10 };
		endNode = tmpVec;
		tmpVec = { (int)boids[49].location.x / 10,(int)boids[49].location.y / 10 };
		startNode = tmpVec;
		if(astar.openList.size()>0 and astar.closedList.size()>0) astar.render();
		astar.cleanWorld();
		astar.update();*/
		
		//Spider
		spider.update();
		spider.render();

		//Inverse Kinematics
		/*SDL_GetMouseState(&x, &y);
		controlPoint.x = x;
		controlPoint.y = y;
		ik.render();*/

		//check for collision on the raycast and update the target position
		//raycast.raycastToMousePosition(player.getPlayerRect(), map.getObstacles());
		
		//Swing and Player
		/*if (swing.isSwinging) swing.createSwing(&player, &raycast);
		if (swing.pointsVector.size() > 0) { swing.updatePlayerPositionSwing(&player); }
		player.move(map.getObstacles());*/

		//swing.update();

		//Render Boids
		/*for (int i = 0; i < boids.size(); i++) {
			target.x = player.getPlayerRect().x;
			target.y = player.getPlayerRect().y;
			boids[i].flock(&boids, target);
			boids[i].collision();
			boids[i].update();
			boids[i].render();
		}*/
		
		//player.render();
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