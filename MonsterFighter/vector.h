#pragma once

class Vector {
public:
	Vector(float _x = 0, float _y = 0);
	void add(Vector v);
	void sub(Vector v);
	void mult(float n);
	void div(float n);
	float mag();
	void normalize();
	void limit(float n);
	float distance(Vector other);

	float x;
	float y;
};
