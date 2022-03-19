#pragma once
#include "IK.h"
#include "globalVariables.h"

class Spider {
public:
	Spider();

	void update();
	void render();
private:
	SDL_Rect body;

	//LEGf-1
	InverseKinematics legF_1;
	InverseKinematics legF_2;
	vec2D legF_1_startingPoint;
	vec2D legF_1_controlPoint;
	vec2D legF_2_startingPoint;
	vec2D legF_2_controlPoint;
	float legF_normalizer;

	//LEGb-2
	InverseKinematics legB_1;
	InverseKinematics legB_2;
	vec2D legB_1_startingPoint;
	vec2D legB_1_controlPoint;
	vec2D legB_2_startingPoint;
	vec2D legB_2_controlPoint;
	float legB_normalizer;

	//update legF_2 & legB_2 control points
	void controlPointManager();
};
