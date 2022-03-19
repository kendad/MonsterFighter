#include "vector.h"
#include <iostream>

Vector::Vector(float _x, float _y) {
	x = _x;
	y = _y;
}

void Vector::add(Vector v) {
	x += v.x;
	y += v.y;
}

void Vector::sub(Vector v) {
	x -= v.x;
	y -= v.y;
}

void Vector::mult(float n) {
	x *= n;
	y *= n;
}

void Vector::div(float n) {
	x /= n;
	y /= n;
}

float Vector::mag() {
	return sqrt(abs(x * x) + abs(y * y));
}

void Vector::normalize() {
	float m = mag();
	if (m != 0) div(m);
}

void Vector::limit(float n) {
	if (x > n) x = n;
	if (y > n) y = n;
}

float Vector::distance(Vector other) {
	Vector tmpVec = Vector(abs(x - other.x), abs(y - other.y));
	float d = sqrt((tmpVec.x * tmpVec.x) + (tmpVec.y * tmpVec.y));
	return d;
}