#pragma once
#include <SDL.h>
#include <vector>
#include "globalVariables.h"

class Raycast {
public:
	//RAYCASTING
	void raycastToMousePosition(SDL_Rect origin, std::vector<SDL_Rect> obstacles);
	//get target position
	vec2D getTargetPosition();
private:
	//LINE-LINE INTERSECTION
	bool isRayLineIntersecting(vec2D p1, vec2D p2, vec2D p3, float directionX, float directionY);//P1 and P2 will belong to the obstacle
	vec2D rayLineIntersectionPoint(float t, float x1, float y1, float x2, float y2);

	//Update target pointer position
	void updateTragetPosition(std::vector<SDL_Rect> obstacles, vec2D rayOrigin, float directionX, float directionY);


	vec2D mtargetPosition;
};
