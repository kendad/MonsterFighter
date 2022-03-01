#include "swing.h"
#include "globalVariables.h"
#include <iostream>

//POINT OBJECT
Point::Point(float _x, float _y, float _oldX, float _oldY, bool _pinned) {
	x = _x;
	y = _y;
	width = 10;
	height = 10;
	oldX = _oldX;
	oldY = _oldY;

	pinned = _pinned;

	bounce = 0.9f;
	friction = 0.9f;
	gravity = 0.8f;
	pointBody = { (int)x,(int)y,width,height };
}

void Point::update() {
	if (!pinned) {
		float vx = x - oldX;
		float vy = y - oldY;

		oldX = x;
		oldY = y;

		x += vx;
		y += vy;
		y += gravity;

		//check for edges
		if (x > SCREEN_WIDTH) {
			x = SCREEN_WIDTH;
			oldX = x + vx * bounce;
		}
		else if (x < 0) {
			x = 0;
			oldX = x + vx * bounce;
		}
		else if (y + height > SCREEN_HEIGHT) {
			y = SCREEN_HEIGHT - height;
			oldY = y + vy * bounce * friction;
		}
		else if (y < 0) {
			y = 0;
			oldY = y + vy * bounce;
		}

		//update pointBody with latest X&Y vals
		pointBody.x = (int)x;
		pointBody.y = (int)y;
	}
}

void Point::render() {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(gRenderer, &pointBody);
}

//STICK OBJECT
Stick::Stick(Point* _p0, Point* _p1) :p0(_p0), p1(_p1) {
	length = distance();
}

float Stick::distance() {
	float dx = p1->x - p0->x;
	float dy = p1->y - p0->y;
	return sqrt((dx * dx) + (dy * dy));
}

void Stick::update() {
	float dx = p1->x - p0->x;
	float dy = p1->y - p0->y;
	float _distance = sqrt((dx * dx) + (dy * dy));
	float _difference = length - _distance;
	float _percent = (_difference / _distance) / 2;
	float _offsetX = dx * _percent;
	float _offsetY = dy * _percent;

	if (!p0->pinned) {
		p0->x -= _offsetX;
		p0->y -= _offsetY;
	}

	if (!p1->pinned) {
		p1->x += _offsetX;
		p1->y += _offsetY;
	}
}

void Stick::render() {
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(gRenderer, p0->x, p0->y, p1->x, p1->y);
}


//SWING OBJECT
Swing::Swing() {
	isSwinging = false;

	pointsVector = std::vector<Point>();
	sticksVector = std::vector<Stick>();

	shouldPlayerMove = false;
	shouldPlayerJump = false;
	div = 20;
}

void Swing::handelUserInput(SDL_Event* e) {
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		if (e->button.button == SDL_BUTTON_LEFT) { isSwinging = true; shouldPlayerJump = false; }
		if (e->button.button == SDL_BUTTON_RIGHT) {
			if (pointsVector.size() > 0) {
				for (int i = 0; i < pointsVector.size(); i++) {
					pointsVector.erase(pointsVector.begin() + i);
				}
			}
		}
	}

	if (e->type == SDL_MOUSEBUTTONUP) {
		if (e->button.button == SDL_BUTTON_LEFT) isSwinging = false;
	}

	if (e->type == SDL_KEYDOWN) {
		if (e->key.keysym.sym == SDLK_e) { pointsVector.clear(); sticksVector.clear(); }
		if (e->key.keysym.sym == SDLK_x) {
			if (pointsVector.size() >= 1) pointsVector.erase(pointsVector.begin());
		}
		if (e->key.keysym.sym == SDLK_d || e->key.keysym.sym == SDLK_a) { shouldPlayerMove = true; }
		if (e->key.keysym.sym == SDLK_SPACE) { if (pointsVector.size() > 0) { pointsVector[0].y -= 30; shouldPlayerJump = true; } }
	}

	if (e->type == SDL_KEYUP) {
		if (e->key.keysym.sym == SDLK_d || e->key.keysym.sym == SDLK_a) { shouldPlayerMove = false; }
	}
}

void Swing::update() {
	if (sticksVector.size() > 0 && pointsVector.size() > 0) {
		for (int i = 0; i < pointsVector.size(); i++) { pointsVector[i].update(); }
		for (int i = 0; i < sticksVector.size(); i++) { sticksVector[i].update(); }
		render();
	}
}

void Swing::createSwing(Player* player, Raycast* raycast) {
	pointsVector.clear();
	sticksVector.clear();

	vec2D dVec = { raycast->getTargetPosition().x - player->getPlayerRect().x,raycast->getTargetPosition().y - player->getPlayerRect().y };
	float d = sqrt(abs(dVec.x * dVec.x) + (dVec.y * dVec.y));
	float directionX = dVec.x / d;
	float directionY = dVec.y / d;

	int numberOfSticks = d / div;
	int numberOfPoints = numberOfSticks + 1;
	for (int i = 0; i < numberOfPoints; i++) {
		Point tmpPoint = Point(player->getPlayerRect().x + (directionX * i * div), player->getPlayerRect().y + (directionY * i * div), player->getPlayerRect().x + (directionX * i * div), player->getPlayerRect().y + (directionY * i * div));
		if (i == numberOfPoints - 1) { tmpPoint.pinned = true; }
		pointsVector.push_back(tmpPoint);
	}
	for (int i = 0; i < pointsVector.size() - 1; i++) {
		Stick tmpStick = Stick(&pointsVector[i], &pointsVector[i + 1]);
		sticksVector.push_back(tmpStick);
	}
}

void Swing::updatePlayerPositionSwing(Player* player) {
	if (shouldPlayerMove && !shouldPlayerJump) {
		pointsVector[0].x = player->mPlayerBody.x;
		player->mPlayerBody.y = pointsVector[0].y;
	}
	else if (!shouldPlayerMove && !shouldPlayerJump) {
		player->mPlayerBody.x = pointsVector[0].x;
		player->mPlayerBody.y = pointsVector[0].y;
	}
}

void Swing::render() {
	/*for (int i = 0; i < pointsVector.size(); i++) {
		pointsVector[i].render();
	}*/
	for (int i = 0; i < sticksVector.size(); i++) {
		sticksVector[i].render();
	}
}