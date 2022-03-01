#pragma once
#include<SDL.h>
#include <vector>
#include "player.h"
#include "raycast.h"

class Point {
public:
	Point(float _x, float _y, float _oldX, float _oldY, bool _pinned = false);
	void update();
	void render();

	float x;
	float y;
	bool pinned;
private:
	int width;
	int height;

	float oldX;
	float oldY;

	//Some forces of Nature
	float bounce;
	float friction;
	float gravity;

	SDL_Rect pointBody;
};

class Stick {
public:
	Stick(Point* _p0, Point* _p1);
	void update();
	void render();
	float distance();
private:
	Point* p0;
	Point* p1;
	float length;
};

class Swing {
public:
	Swing();
	void update();
	void render();

	bool isSwinging;
	void handelUserInput(SDL_Event* e);

	void createSwing(Player* player, Raycast* raycast);
	void updatePlayerPositionSwing(Player* player);

	std::vector<Point> pointsVector;
	std::vector<Stick> sticksVector;
private:
	bool shouldPlayerMove;
	bool shouldPlayerJump;
	int div;
};