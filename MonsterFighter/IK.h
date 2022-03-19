#pragma once
#include "globalVariables.h"
#include <SDL.h>
#include <vector>

class InverseKinematics {
public:
	InverseKinematics();
	InverseKinematics(int numberOfJoints, int _length, vec2D* _startPoint, vec2D* _controlPoint);
	void render();
	std::vector<vec2D> getJoints();
private:
	void backward();
	void forward();

	vec2D* controlPoint;
	vec2D* startPoint;
	int length;
	std::vector<vec2D> joints;
};

