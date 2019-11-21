#pragma once
#include <math.h>
#include "Lib.hpp"

class SphereCollider {

public:
	Vector2i a1;
	Vector2i a2;
	Vector2i a3;
	Vector2i a4;
	Vector2i a5;
	Vector2i a6;
	Vector2i a7;
	Vector2i a8;

	Vector2i a15;
	Vector2i a25;
	Vector2i a35;
	Vector2i a45;
	Vector2i a55;
	Vector2i a65;
	Vector2i a75;
	Vector2i a85;

	SphereCollider(Vector2f Origin, float rayon) {
		a1 = (Vector2i(Origin.x + rayon, Origin.y));
		a2 = (Vector2i(Origin.x + ((sqrt(2) / 2) * rayon), Origin.y + ((sqrt(2) / 2) * rayon)));
		a3 = (Vector2i(Origin.x , Origin.y + rayon));
		a4 = (Vector2i(Origin.x - ((sqrt(2) / 2) * rayon), Origin.y + ((sqrt(2) / 2) * rayon)));
		a5 = (Vector2i(Origin.x - rayon, Origin.y));
		a6 = (Vector2i(Origin.x - ((sqrt(2) / 2) * rayon), Origin.y - ((sqrt(2) / 2) * rayon)));
		a7 = (Vector2i(Origin.x ,  Origin.y - rayon));
		a8 = (Vector2i(Origin.x + ((sqrt(2) / 2) * rayon), Origin.y - ((sqrt(2) / 2) * rayon)));

		a15 = (Vector2i(Origin.x + ((sqrt(3) / 2) * rayon), Origin.y + 1 / 2 * rayon));
		a25 = (Vector2i(Origin.x + 1 / 2 * rayon, Origin.y + (sqrt(3) / 2) * rayon));
		a35 = (Vector2i(Origin.x - ((sqrt(3) / 2) * rayon), Origin.y + 1 / 2 * rayon));
		a45 = (Vector2i(Origin.x - 1 / 2 * rayon, Origin.y + (sqrt(3) / 2) * rayon));
		a55 = (Vector2i(Origin.x - ((sqrt(3) / 2) * rayon), Origin.y - 1 / 2 * rayon));
		a65 = (Vector2i(Origin.x - 1 / 2 * rayon, Origin.y - (sqrt(3) / 2) * rayon));
		a75 = (Vector2i(Origin.x + ((sqrt(3) / 2) * rayon), Origin.y - 1 / 2 * rayon));
		a85 = (Vector2i(Origin.x + 1 / 2 * rayon, Origin.y - (sqrt(3) / 2) * rayon));
	}

void Update(Vector2f Origin, float rayon) {
	a1 = (Vector2i(Origin.x + rayon, Origin.y));
	a2 = (Vector2i(Origin.x + ((sqrt(2) / 2) * rayon), Origin.y + ((sqrt(2) / 2) * rayon)));
	a3 = (Vector2i(Origin.x, Origin.y + rayon));
	a4 = (Vector2i(Origin.x - ((sqrt(2) / 2) * rayon), Origin.y + ((sqrt(2) / 2) * rayon)));
	a5 = (Vector2i(Origin.x - rayon, Origin.y));
	a6 = (Vector2i(Origin.x - ((sqrt(2) / 2) * rayon), Origin.y - ((sqrt(2) / 2) * rayon)));
	a7 = (Vector2i(Origin.x, Origin.y - rayon));
	a8 = (Vector2i(Origin.x + ((sqrt(2) / 2) * rayon), Origin.y - ((sqrt(2) / 2) * rayon)));

	a15 = (Vector2i(Origin.x + ((sqrt(3) / 2) * rayon), Origin.y + 1 / 2 * rayon));
	a25 = (Vector2i(Origin.x + 1 / 2 * rayon, Origin.y + (sqrt(3) / 2) * rayon));
	a35 = (Vector2i(Origin.x - ((sqrt(3) / 2) * rayon), Origin.y + 1 / 2 * rayon));
	a45 = (Vector2i(Origin.x - 1 / 2 * rayon, Origin.y + (sqrt(3) / 2) * rayon));
	a55 = (Vector2i(Origin.x - ((sqrt(3) / 2) * rayon), Origin.y - 1 / 2 * rayon));
	a65 = (Vector2i(Origin.x - 1 / 2 * rayon, Origin.y - (sqrt(3) / 2) * rayon));
	a75 = (Vector2i(Origin.x + ((sqrt(3) / 2) * rayon), Origin.y - 1 / 2 * rayon));
	a85 = (Vector2i(Origin.x + 1 / 2 * rayon, Origin.y - (sqrt(3) / 2) * rayon));
}
};

class SquareCollider {

public: 
	Rect<int> Collider;

	Vector2f PrevPos;

	SquareCollider(int Left, int Up, int Width, int Height )
	{
		Collider.left = Left;
		Collider.top = Up;
		Collider.width = Width;
		Collider.height = Height;
	}

void update(int Left, int Up, int Width, int Height)
{
	Collider.left = Left;
	Collider.top = Up;
	Collider.width = Width;
	Collider.height = Height;
}

bool CheckColliding(SquareCollider other) 
	{
	if (Collider.intersects(other.Collider)) return true;
	else return false;
	}
float GetAngleOfCollision(SphereCollider other2)
{
	float pi = 3.14159265358979323846;
	for (int i = 1; i < 17; i++) {
		if (i == 1) {
			if (Collider.contains(other2.a1)) { return 0; }
		}
		else if (i == 3) {
			if (Collider.contains(other2.a2)) { return pi/4; }
		}
		else if (i == 5) {
			if (Collider.contains(other2.a3)) { return pi/2; }
		}
		else if (i == 7) {
			if (Collider.contains(other2.a4)) { return 3*pi/4; }
		}
		else if (i == 9) {
			if (Collider.contains(other2.a5)) { return pi; }
		}
		else if (i == 11) {
			if (Collider.contains(other2.a6)) { return 5*pi/4; }
		}
		else if (i == 13) {
			if (Collider.contains(other2.a7)) { return 3*pi/2; }
		}
		else if (i == 15) {
			if (Collider.contains(other2.a8)) { return 7*pi/4; }
		}
		else if (i == 2) {
			if (Collider.contains(other2.a15)) { return pi/6; }
		}
		else if (i == 4) {
			if (Collider.contains(other2.a25)) { return pi/3; }
		}
		else if (i == 6) {
			if (Collider.contains(other2.a35)) { return 5*pi/6; }
		}
		else if (i == 8) {
			if (Collider.contains(other2.a45)) { return 2*pi/3; }
		}
		else if (i == 10) {
			if (Collider.contains(other2.a55)) { return 7*pi/6; }
		}
		else if (i == 12) {
			if (Collider.contains(other2.a65)) { return 4*pi/3; }
		}
		else if (i == 14) {
			if (Collider.contains(other2.a75)) { return 11*pi/6; }
		}
		else if (i == 16) {
			if (Collider.contains(other2.a85)) { return 5*pi/3; }
		}
	}
	return 0;
}

bool CheckCollidingWithSphere(SphereCollider other2)
{
	for (int i = 1; i < 17; i++) {
		if (i == 1) {
			if (Collider.contains(other2.a1)) { return true; }
		}
		else if (i == 3) {
				if (Collider.contains(other2.a2)) { return true; }
		}
		else if (i == 5) {
				if (Collider.contains(other2.a3)) { return true; }
		}
		else if (i == 7) {
				if (Collider.contains(other2.a4)) { return true; }
		}
		else if (i == 9) {
				if (Collider.contains(other2.a5)) { return true; }
		}
		else if (i == 11) {
				if (Collider.contains(other2.a6)) { return true; }
		}
		else if (i == 13) {
				if (Collider.contains(other2.a7)) { return true; }
		}
		else if (i == 15) {
				if (Collider.contains(other2.a8)) { return true; }
		}
		else if (i == 2) {
			if (Collider.contains(other2.a15)) { return true; }
		}
		else if (i == 4) {
			if (Collider.contains(other2.a25)) { return true; }
		}
		else if (i == 6) {
			if (Collider.contains(other2.a35)) { return true; }
		}
		else if (i == 8) {
			if (Collider.contains(other2.a45)) { return true; }
		}
		else if (i == 10) {
			if (Collider.contains(other2.a55)) { return true; }
		}
		else if (i == 12) {
			if (Collider.contains(other2.a65)) { return true; }
		}
		else if (i == 14) {
			if (Collider.contains(other2.a75)) { return true; }
		}
		else if (i == 16) {
			if (Collider.contains(other2.a85)) { return true; }
		}
	}
	return false;
}

};

