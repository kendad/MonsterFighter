#pragma once
#include "vector.h"
#include "globalVariables.h"
#include <SDL.h>
#include <vector>
#include "texture.h"

class Boid {
public:
	Boid(float x, float y);
	void update();
	void applyForce(Vector force);

	void flock(std::vector<Boid>* boids, Vector target);
	Vector seek(Vector target);
	Vector seperate(std::vector<Boid>* boids);
	Vector align(std::vector<Boid>* boids);
	Vector cohesion(std::vector<Boid>* boids);

	void collision();

	void render();
private:
	Vector location;
	Vector velocity;
	Vector acceleration;

	float maxSpeed;
	float maxForce;

	Texture boidTexture;
	SDL_Rect animationFrame[10];
	int currentAnimationFrame;
	int animationTime;
	SDL_Rect displayRect;
};

