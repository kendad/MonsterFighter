#include "raycast.h"

//RAYCASTING
void Raycast::raycastToMousePosition(SDL_Rect origin, std::vector<SDL_Rect> obstacles) {
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	float directionX = mouseX - origin.x;
	float directionY = mouseY - origin.y;
	float magnitude = sqrt(abs(directionX * directionX) + abs(directionY + directionY));

	if (magnitude != 0) {
		directionX = directionX / magnitude;
		directionY = directionY / magnitude;
	}

	//go through the obstacles and return the update the target position
	vec2D rayOrigin = { origin.x + (origin.w / 2),origin.y + (origin.h / 2) };
	updateTragetPosition(obstacles, rayOrigin, directionX, directionY);

	//Draw the raycast lines
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(gRenderer, origin.x + (origin.w / 2), origin.y + (origin.h / 2), (origin.x + (origin.w / 2)) + directionX * SCREEN_WIDTH, (origin.y + (origin.h / 2)) + directionY * SCREEN_HEIGHT);
}


//LINE-LINE INTERSECTION
bool Raycast::isRayLineIntersecting(vec2D p1, vec2D p2, vec2D p3, float directionX, float directionY) {
	//OBSTACLE-t
	float x1 = p1.x;
	float y1 = p1.y;
	float x2 = p2.x;
	float y2 = p2.y;

	//RAY-u
	float x3 = p3.x;
	float y3 = p3.y;
	float x4 = p3.x + directionX * SCREEN_WIDTH;
	float y4 = p3.y + directionY * SCREEN_HEIGHT;
	float d = ((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4));

	if (d == 0) {
		return false;//the lines are parallel
	}

	float t = (((x1 - x3) * (y3 - y4)) - ((y1 - y3) * (x3 - x4))) / d;
	float u = ((((x1 - x3) * (y1 - y2)) - ((y1 - y3) * (x1 - x2))) / d);

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
		mtargetPosition = rayLineIntersectionPoint(t, x1, y1, x2, y2);
		return true;
	}
	else {
		return false;
	}
}


vec2D Raycast::rayLineIntersectionPoint(float t, float x1, float y1, float x2, float y2) {
	vec2D intersectionPoint = { x1 + (t * (x2 - x1)),y1 + (t * (y2 - y1)) };
	return intersectionPoint;
}

//Update target pointer position
void Raycast::updateTragetPosition(std::vector<SDL_Rect> obstacles, vec2D rayOrigin, float directionX, float directionY) {
	//check world obstacles for collisions
	for (int i = 0; i < obstacles.size(); i++) {
		for (int j = 1; j <= 4; j++) {
			vec2D wallP0 = {};
			vec2D wallP1 = {};
			int rectYPosModifier = 0;
			int rectXPosModifier = 0;

			if (j == 1 && rayOrigin.y <= obstacles[i].y) { wallP0 = { obstacles[i].x,obstacles[i].y }; wallP1 = { obstacles[i].x + obstacles[i].w,obstacles[i].y }; rectYPosModifier = 10; }//top
			if (j == 2 && rayOrigin.x >= obstacles[i].x + obstacles[i].w) { wallP0 = { obstacles[i].x + obstacles[i].w,obstacles[i].y }; wallP1 = { obstacles[i].x + obstacles[i].w,obstacles[i].y + obstacles[i].h }; }//right
			if (j == 3 && rayOrigin.y >= obstacles[i].y + obstacles[i].h) { wallP0 = { obstacles[i].x + obstacles[i].w,obstacles[i].y + obstacles[i].h }; wallP1 = { obstacles[i].x,obstacles[i].y + obstacles[i].h }; }//bottom
			if (j == 4 && rayOrigin.x <= obstacles[i].x) { wallP0 = { obstacles[i].x,obstacles[i].y + obstacles[i].h }; wallP1 = { obstacles[i].x,obstacles[i].y }; rectXPosModifier = 10; }//left

			if (isRayLineIntersecting(wallP0, wallP1, rayOrigin, directionX, directionY)) {
				SDL_Rect tmpRect = { mtargetPosition.x - rectXPosModifier,mtargetPosition.y - rectYPosModifier,10,10 };
				SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
				SDL_RenderDrawRect(gRenderer, &tmpRect);
				return;
			}
		}
	}

	//check screen edges for ray collisions
	for (int i = 1; i <= 4; i++) {
		vec2D wallP0 = {};
		vec2D wallP1 = {};
		int rectYPosModifier = 0;
		int rectXPosModifier = 0;
		if (i == 1) { wallP0 = { SCREEN_WIDTH,0 }; wallP1 = { 0,0 }; }
		if (i == 2) { wallP0 = { SCREEN_WIDTH,0 }; wallP1 = { SCREEN_WIDTH,SCREEN_HEIGHT }; rectXPosModifier = 10; }
		if (i == 3) { wallP0 = { SCREEN_WIDTH,SCREEN_HEIGHT }; wallP1 = { 0,SCREEN_HEIGHT }; rectYPosModifier = 10; }
		if (i == 4) { wallP0 = { 0,SCREEN_HEIGHT }; wallP1 = { 0,0 }; }

		if (isRayLineIntersecting(wallP0, wallP1, rayOrigin, directionX, directionY)) {
			SDL_Rect tmpRect = { mtargetPosition.x - rectXPosModifier,mtargetPosition.y - rectYPosModifier,10,10 };
			SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(gRenderer, &tmpRect);
			return;
		}
	}
}

//Get target position
vec2D Raycast::getTargetPosition() {
	return mtargetPosition;
}