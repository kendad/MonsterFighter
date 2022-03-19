#include "IK.h"
#include <iostream>

InverseKinematics::InverseKinematics() {

}

InverseKinematics::InverseKinematics(int numberOfJoints, int _length, vec2D* _startPoint, vec2D* _controlPoint) {
	//update the length
	length = _length;
	startPoint = _startPoint;
	//update the control Point
	controlPoint = _controlPoint;

	//add starting join to the front of the stack
	joints.push_back(*startPoint);

	//create rest of the joints
	for (int i = 0; i < numberOfJoints - 1; i++) {
		vec2D tmpVec = { joints[i].x + length,joints[i].y };
		joints.push_back(tmpVec);
	}
}

void InverseKinematics::backward() {
	float distance = sqrt(abs(pow(controlPoint->x - joints[joints.size() - 1].x, 2) + pow(controlPoint->y - joints[joints.size() - 1].y, 2)));
	if (distance > 1) {
		joints[joints.size() - 1] = *controlPoint;//set the end point of the IK to the control point
		for (int i = joints.size() - 1; i >= 1; i--) {
			float mag = sqrt(abs(pow((joints[i - 1].x - joints[i].x), 2)) + abs(pow((joints[i - 1].y - joints[i].y), 2)));
			float dirX = (joints[i - 1].x - joints[i].x) / mag;
			float dirY = (joints[i - 1].y - joints[i].y) / mag;
			float updatedX = joints[i].x + (dirX * length);
			float updatedY = joints[i].y + (dirY * length);
			joints[i - 1] = { (int)updatedX,(int)updatedY };
		}
	}
}

void InverseKinematics::forward() {
	float distance = sqrt(abs(pow(startPoint->x - joints[joints.size() - 1].x, 2) + pow(startPoint->y - joints[joints.size() - 1].y, 2)));
	if (distance > 1) {
		joints[0] = *startPoint;
		for (int i = 0; i <= joints.size() - 2; i++) {
			float mag = sqrt(abs(pow((joints[i + 1].x - joints[i].x), 2)) + abs(pow((joints[i + 1].y - joints[i].y), 2)));
			float dirX = (joints[i + 1].x - joints[i].x) / mag;
			float dirY = (joints[i + 1].y - joints[i].y) / mag;
			float updatedX = joints[i].x + (dirX * length);
			float updatedY = joints[i].y + (dirY * length);
			joints[i + 1] = { (int)updatedX,(int)updatedY };
		}
	}
}

void InverseKinematics::render() {
	backward();
	forward();

	//render the points
	for (int i = 0; i < joints.size(); i++) {
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 0, 255);
		SDL_Rect tmpRect = { joints[i].x,joints[i].y,10,10 };
		SDL_RenderFillRect(gRenderer, &tmpRect);
	}
	//render the lines
	for (int i = 0; i < joints.size() - 1; i++) {
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(gRenderer, joints[i].x, joints[i].y, joints[i + 1].x, joints[i + 1].y);
	}
}

std::vector<vec2D> InverseKinematics::getJoints() { return joints; }