#pragma once
#include <SDL.h>
#include <vector>

class Map {
public:
	Map();
	void renderObstacles();
	void updateWorldMatrix();
	std::vector<SDL_Rect> getObstacles();
private:
	std::vector<SDL_Rect> obstaclesList;
};

