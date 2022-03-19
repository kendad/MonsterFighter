#include "boid.h"
#include "basicFunctionalities.h"
#include <iostream>

Boid::Boid(float x, float y) {
	location = Vector(x, y);
	velocity = Vector(0, 0);
	acceleration = Vector(0, 0);

	maxSpeed = 4;
	maxForce = 0.1;

	boidTexture.loadFromFile("Assets/fire.png");
	currentAnimationFrame = 0;
	animationTime = SDL_GetTicks();
	animationFrame[0] = { 21,12,25,45 };
	animationFrame[1] = { 86,11,24,47 };
	animationFrame[2] = { 150,10,23,48 };
	animationFrame[3] = { 214,9,23,49 };
	animationFrame[4] = { 279,8,21,52 };
	animationFrame[5] = { 343,6,21,54 };
	animationFrame[6] = { 406,6,22,54 };
	animationFrame[7] = { 470,5,23,55 };
	animationFrame[8] = { 534,12,23,48 };
	animationFrame[9] = { 597,11,25,49 };


	displayRect = { (int)location.x,(int)location.y,10,10 };
}

void Boid::update() {
	velocity.add(acceleration);
	velocity.limit(maxSpeed);
	location.add(velocity);
	acceleration.mult(0);

	//update the display rect
	displayRect.x = (int)location.x;
	displayRect.y = (int)location.y;
}

void Boid::applyForce(Vector force) {
	acceleration.add(force);
}

void Boid::flock(std::vector<Boid>* boids, Vector target) {
	Vector seeker = seek(target);
	Vector sep = seperate(boids);
	Vector ali = align(boids);
	Vector coh = cohesion(boids);

	sep.mult(0.3);
	ali.mult(1.0);
	coh.mult(0.5);
	seeker.mult(0.3);

	applyForce(seeker);
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

Vector Boid::seek(Vector target) {
	Vector desired = Vector(target.x - location.x, target.y - location.y);
	desired.normalize();
	desired.mult(maxSpeed);

	Vector steerForce = Vector(desired.x - velocity.x, desired.y - velocity.y);
	steerForce.limit(maxForce);
	return steerForce;
}

Vector Boid::seperate(std::vector<Boid>* boids) {
	Vector steerForce = Vector();
	float desiredSeperation = 20;
	Vector sum = Vector();
	int count = 0;
	for (int i = 0; i < boids->size(); i++) {
		float d = location.distance(boids->at(i).location);
		if ((d > 0) && (d < desiredSeperation)) {
			Vector diff = Vector(location.x - boids->at(i).location.x, location.y - boids->at(i).location.y);
			diff.normalize();
			diff.div(d);
			sum.add(diff);
			count++;
		}
	}

	if (count > 0) {
		sum.div(count);
		sum.normalize();
		sum.mult(maxSpeed);
		steerForce = Vector(sum.x - velocity.x, sum.y - velocity.y);
		return steerForce;
	}
	else {
		return steerForce;
	}
}


Vector Boid::align(std::vector<Boid>* boids) {
	Vector steerForce = Vector();
	Vector sum = Vector();
	float nearest = 50;
	int count = 0;
	for (int i = 0; i < boids->size(); i++) {
		float d = location.distance(boids->at(i).location);
		if ((d > 0) && (d < nearest)) {
			sum.add(boids->at(i).velocity);
			count++;
		}
	}

	if (count > 0) {
		sum.div(count);
		sum.normalize();
		sum.mult(maxSpeed);
		steerForce = Vector(sum.x - velocity.x, sum.y - velocity.y);
		return steerForce;
	}
	else { return steerForce; }
}


Vector Boid::cohesion(std::vector<Boid>* boids) {
	Vector steerForce = Vector();
	Vector sum = Vector();
	float nearest = 50;
	int count = 0;
	for (int i = 0; i < boids->size(); i++) {
		float d = location.distance(boids->at(i).location);
		if ((d > 0) && (d < nearest)) {
			sum.add(boids->at(i).location);
			count++;
		}
	}

	if (count > 0) {
		sum.div(count);
		steerForce = Vector(sum.x - velocity.x, sum.y - velocity.y);
		steerForce.limit(maxForce);
		return steerForce;
	}
	else { return steerForce; }
}

void Boid::collision() {
	if (location.x < 0) { velocity.x *= -1; location.x = 10; }
	if (location.x + displayRect.w > SCREEN_WIDTH) { velocity.x *= -1; location.x = SCREEN_WIDTH - displayRect.w - 10; }
	if (location.y < 0) { velocity.y *= -1; location.y = 10; }
	if (location.y + displayRect.h > SCREEN_HEIGHT) { velocity.y *= -1; location.y = SCREEN_HEIGHT - displayRect.h - 10; }

	for (int i = 0; i < worldObstacles.size(); i++) {
		SDL_Rect tmpRect = { location.x,location.y,displayRect.w,displayRect.h };
		if (checkCollision(tmpRect, worldObstacles[i])) {
			//check vertical collision
			if (tmpRect.y <= worldObstacles[i].y + worldObstacles[i].h && tmpRect.y + tmpRect.h > worldObstacles[i].y + worldObstacles[i].h) {
				location.y = worldObstacles[i].y + worldObstacles[i].h;
			}
			if (tmpRect.y + tmpRect.h >= worldObstacles[i].y && tmpRect.y < worldObstacles[i].y) {
				location.y = worldObstacles[i].y - tmpRect.h;
			}
			//check horizontal collision
			if (tmpRect.x <= worldObstacles[i].x + worldObstacles[i].w && tmpRect.x + tmpRect.w > worldObstacles[i].x + worldObstacles[i].w) {
				location.x = worldObstacles[i].x + worldObstacles[i].w;
			}
			if (tmpRect.x < worldObstacles[i].x && tmpRect.x + tmpRect.w >= worldObstacles[i].x) {
				location.x = worldObstacles[i].x - 20;
			}
		}
	}
}

void Boid::render() {
	//render boids as triangles
	int r = 5;
	float heading = atan2(velocity.x, velocity.y);
	float theta = heading + M_PI / 2;

	/*float x_prime_1 = ((location.x - (location.x)) * cos(theta)) - ((location.y - (location.y + r)) * sin(theta)) + (location.x);
	float y_prime_1 = ((location.x - (location.x)) * sin(theta)) + ((location.y - (location.y + r)) * cos(theta)) + (location.y + r);
	float y_prime_1_arrow = ((location.x - (location.x)) * sin(theta)) + (((location.y+20) - (location.y + r)) * cos(theta)) + (location.y + r);

	float x_prime_2 = (((location.x + r) - (location.x)) * cos(theta)) - (((location.y + r) - (location.y + r)) * sin(theta)) + (location.x);
	float y_prime_2 = (((location.x + r) - (location.x)) * sin(theta)) + (((location.y + r) - (location.y + r)) * cos(theta)) + (location.y + r);

	float x_prime_3 = (((location.x + r) - (location.x)) * cos(theta)) - (((location.y - r) - (location.y + r)) * sin(theta)) + (location.x);
	float y_prime_3 = (((location.x + r) - (location.x)) * sin(theta)) + (((location.y - r) - (location.y + r)) * cos(theta)) + (location.y + r);

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);

	SDL_RenderDrawLine(gRenderer, x_prime_1, y_prime_1, x_prime_2, y_prime_2);
	SDL_RenderDrawLine(gRenderer, x_prime_1, y_prime_1, x_prime_3, y_prime_3);
	SDL_RenderDrawLine(gRenderer, x_prime_2, y_prime_2, x_prime_3, y_prime_3);*/

	//render boids as animated texture
	boidTexture.render(location.x, location.y, &animationFrame[currentAnimationFrame], theta * 57.296);
	if (SDL_GetTicks() - animationTime >= 10) {
		currentAnimationFrame++;
		if (currentAnimationFrame > 9) currentAnimationFrame = 0;
		animationTime = SDL_GetTicks();
	}
}