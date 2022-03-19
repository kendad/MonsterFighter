#include "map.h"
#include "globalVariables.h"

Map::Map() {
	obstaclesList = std::vector<SDL_Rect>();
	SDL_Rect tmpObs = { 0,200,500,50 };
	obstaclesList.push_back(tmpObs);
	//tmpObs = { 0,100,300,10 };
	obstaclesList.push_back(tmpObs);
	tmpObs = { SCREEN_WIDTH - 500,400,500,50 };
	obstaclesList.push_back(tmpObs);
	worldObstacles = obstaclesList;
	//update the world matrix with all the obstacles
	updateWorldMatrix();
}

std::vector<SDL_Rect> Map::getObstacles() { return obstaclesList; }

void Map::renderObstacles() {
	for (int i = 0; i < obstaclesList.size(); i++) {
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer, &obstaclesList[i]);
	}
}

void Map::updateWorldMatrix() {
	for (int y = 0; y < SCREEN_HEIGHT / 10; y++) {
		for (int x = 0; x < SCREEN_WIDTH / 10; x++) {
			worldMatrix[x][y] = 0;
		}
	}
	//convert screen space to grid space and then update the grid space with obstacles
	for (int i = 0; i < obstaclesList.size(); i++) {
		for (int x = obstaclesList[i].x; x < obstaclesList[i].x + obstaclesList[i].w; x += 10) {
			for (int y = obstaclesList[i].y; y < obstaclesList[i].y + obstaclesList[i].h; y += 10) {
				worldMatrix[x / 10][y / 10] = 1;
			}
		}
	}
}