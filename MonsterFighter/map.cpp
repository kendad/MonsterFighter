#include "map.h"
#include "globalVariables.h"

Map::Map() {
	obstaclesList = std::vector<SDL_Rect>();
	SDL_Rect tmpObs = { 0,200,300,50 };
	obstaclesList.push_back(tmpObs);
	//tmpObs = { 0,100,300,10 };
	obstaclesList.push_back(tmpObs);
	tmpObs = { SCREEN_WIDTH - 200,400,200,50 };
	obstaclesList.push_back(tmpObs);
}

std::vector<SDL_Rect> Map::getObstacles() { return obstaclesList; }

void Map::renderObstacles() {
	for (int i = 0; i < obstaclesList.size(); i++) {
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer, &obstaclesList[i]);
	}
}