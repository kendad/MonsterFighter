#include "spider.h"
#include <iostream>
#include "basicFunctionalities.h"

Spider::Spider() {
	body = { 100,SCREEN_HEIGHT / 2 ,50,50 };

	//FRONT LEGS
	legF_1_startingPoint = { body.x + body.w,body.y };
	legF_1_controlPoint = { body.x + body.w + 100,body.y - 50 };
	legF_1 = InverseKinematics(2, 100, &legF_1_startingPoint, &legF_1_controlPoint);
	legF_2_startingPoint = { legF_1.getJoints()[legF_1.getJoints().size() - 1].x,legF_1.getJoints()[legF_1.getJoints().size() - 1].y };
	legF_2_controlPoint = { body.x + body.w + 80,body.y + body.h };
	legF_2 = InverseKinematics(2, 100, &legF_2_startingPoint, &legF_2_controlPoint);
	legF_normalizer = 0;

	//BACK LEGS
	legB_1_startingPoint = { body.x,body.y };
	legB_1_controlPoint = { body.x - 100,body.y - 50 };
	legB_1 = InverseKinematics(2, 100, &legB_1_startingPoint, &legB_1_controlPoint);
	legB_2_startingPoint = { legB_1.getJoints()[legB_1.getJoints().size() - 1].x,legB_1.getJoints()[legB_1.getJoints().size() - 1].y };
	legB_2_controlPoint = { body.x - 80,body.y + body.h };
	legB_2 = InverseKinematics(2, 100, &legB_2_startingPoint, &legB_2_controlPoint);
	legB_normalizer = 0;
}

void Spider::controlPointManager() {
	float d1 = abs(legF_2_controlPoint.x - (body.x + body.w));//when d1 decreases->interpolate
	float d2 = abs(body.x - legB_2_controlPoint.x);//when d2 increases->interpolate
	//Front Legs
	if (d1 < 60) {
		legF_2_controlPoint.x = lerp(legF_normalizer, legF_2_controlPoint.x, legF_2_controlPoint.x + 400);
		legF_1_controlPoint.x = lerp(legF_normalizer, legF_1_controlPoint.x, legF_1_controlPoint.x - 40);
		legF_normalizer += 0.05;
		if (legF_normalizer > 1) legF_normalizer = 0;
	}
	else
		if (d1 > 150) {
			legF_2_controlPoint.x = lerp(legF_normalizer, legF_2_controlPoint.x - 80, legF_2_controlPoint.x);
			legF_1_controlPoint.x = lerp(legF_normalizer, legF_1_controlPoint.x, legF_1_controlPoint.x + 40);
			legF_normalizer += 0.05;
			if (legF_normalizer > 1) legF_normalizer = 0;
		}
		else

			//Back Legs
			if (d2 < 60) {
				legB_2_controlPoint.x = lerp(legB_normalizer, legB_2_controlPoint.x, legB_2_controlPoint.x - 400);
				legB_1_controlPoint.x = lerp(legB_normalizer, legB_1_controlPoint.x, legB_1_controlPoint.x + 40);
				legB_normalizer += 0.05;
				if (legB_normalizer > 1) legB_normalizer = 0;
			}
			else
				if (d2 > 150) {
					legB_2_controlPoint.x = lerp(legB_normalizer, legB_2_controlPoint.x + 80, legB_2_controlPoint.x);
					legB_1_controlPoint.x = lerp(legB_normalizer, legB_1_controlPoint.x, legB_1_controlPoint.x - 40);
					legB_normalizer += 0.05;
					if (legB_normalizer > 1) legB_normalizer = 0;
				}
}

void Spider::update() {
	body.x += 1;

	legF_1_startingPoint = { body.x + body.w,body.y };
	legF_1_controlPoint = { body.x + body.w + 100,body.y - 50 };
	legF_2_startingPoint = { legF_1.getJoints()[legF_1.getJoints().size() - 1].x,legF_1.getJoints()[legF_1.getJoints().size() - 1].y };
	legF_2_controlPoint.y = body.y + body.h;
	legB_1_startingPoint = { body.x,body.y };
	legB_1_controlPoint = { body.x - 100,body.y - 50 };
	legB_2_startingPoint = { legB_1.getJoints()[legB_1.getJoints().size() - 1].x,legB_1.getJoints()[legB_1.getJoints().size() - 1].y };
	legB_2_controlPoint.y = body.y + body.h;
	controlPointManager();
}

void Spider::render() {
	SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
	SDL_RenderFillRect(gRenderer, &body);

	//FRONT LEGS
	legF_1.render();
	legF_2.render();

	//BACK LEGS
	legB_1.render();
	legB_2.render();
}