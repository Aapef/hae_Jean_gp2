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
/*
	Vector2i a15;
	Vector2i a25;
	Vector2i a35;
	Vector2i a45;
	Vector2i a55;
	Vector2i a65;
	Vector2i a75;
	Vector2i a85;*/

	SphereCollider(Vector2f Origin, float rayon) {
		a1 = (Vector2i(Origin.x + rayon, Origin.y));
		a2 = (Vector2i(Origin.x + ((sqrt(2) / 2) * rayon), Origin.y - ((sqrt(2) / 2) * rayon)));
		a3 = (Vector2i(Origin.x , Origin.y - rayon));
		a4 = (Vector2i(Origin.x - ((sqrt(2) / 2) * rayon), Origin.y - ((sqrt(2) / 2) * rayon)));
		a5 = (Vector2i(Origin.x - rayon, Origin.y));
		a6 = (Vector2i(Origin.x - ((sqrt(2) / 2) * rayon), Origin.y + ((sqrt(2) / 2) * rayon)));
		a7 = (Vector2i(Origin.x ,  Origin.y + rayon));
		a8 = (Vector2i(Origin.x + ((sqrt(2) / 2) * rayon), Origin.y + ((sqrt(2) / 2) * rayon)));

		/*a15 = (Vector2i(Origin.x + ((sqrt(3) / 2) * rayon), Origin.y + 1 / 2 * rayon));
		a25 = (Vector2i(Origin.x + 1 / 2 * rayon, Origin.y + (sqrt(3) / 2) * rayon));
		a35 = (Vector2i(Origin.x - ((sqrt(3) / 2) * rayon), Origin.y + 1 / 2 * rayon));
		a45 = (Vector2i(Origin.x - 1 / 2 * rayon, Origin.y + (sqrt(3) / 2) * rayon));
		a55 = (Vector2i(Origin.x - ((sqrt(3) / 2) * rayon), Origin.y - 1 / 2 * rayon));
		a65 = (Vector2i(Origin.x - 1 / 2 * rayon, Origin.y - (sqrt(3) / 2) * rayon));
		a75 = (Vector2i(Origin.x + ((sqrt(3) / 2) * rayon), Origin.y - 1 / 2 * rayon));
		a85 = (Vector2i(Origin.x + 1 / 2 * rayon, Origin.y - (sqrt(3) / 2) * rayon));*/
	}

void Update(Vector2f Origin, float rayon) {
	a1 = (Vector2i(Origin.x + rayon, Origin.y));
	a2 = (Vector2i(Origin.x + ((sqrt(2) / 2) * rayon), Origin.y - ((sqrt(2) / 2) * rayon)));
	a3 = (Vector2i(Origin.x, Origin.y - rayon));
	a4 = (Vector2i(Origin.x - ((sqrt(2) / 2) * rayon), Origin.y - ((sqrt(2) / 2) * rayon)));
	a5 = (Vector2i(Origin.x - rayon, Origin.y));
	a6 = (Vector2i(Origin.x - ((sqrt(2) / 2) * rayon), Origin.y + ((sqrt(2) / 2) * rayon)));
	a7 = (Vector2i(Origin.x, Origin.y + rayon));
	a8 = (Vector2i(Origin.x + ((sqrt(2) / 2) * rayon), Origin.y + ((sqrt(2) / 2) * rayon)));

	/*a15 = (Vector2i(Origin.x + ((sqrt(3) / 2) * rayon), Origin.y + 1 / 2 * rayon));
	a25 = (Vector2i(Origin.x + 1 / 2 * rayon, Origin.y + (sqrt(3) / 2) * rayon));
	a35 = (Vector2i(Origin.x - ((sqrt(3) / 2) * rayon), Origin.y + 1 / 2 * rayon));
	a45 = (Vector2i(Origin.x - 1 / 2 * rayon, Origin.y + (sqrt(3) / 2) * rayon));
	a55 = (Vector2i(Origin.x - ((sqrt(3) / 2) * rayon), Origin.y - 1 / 2 * rayon));
	a65 = (Vector2i(Origin.x - 1 / 2 * rayon, Origin.y - (sqrt(3) / 2) * rayon));
	a75 = (Vector2i(Origin.x + ((sqrt(3) / 2) * rayon), Origin.y - 1 / 2 * rayon));
	a85 = (Vector2i(Origin.x + 1 / 2 * rayon, Origin.y - (sqrt(3) / 2) * rayon));*/
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
		if (Collider.contains(other2.a1) || Collider.contains(other2.a5)) { return 0; }
		if (Collider.contains(other2.a3) || Collider.contains(other2.a7)) { return 1; }
	}

bool CheckCollidingWithSphere(SphereCollider other2)
	{
	if (Collider.contains(other2.a1) || Collider.contains(other2.a3) || Collider.contains(other2.a5) || Collider.contains(other2.a7)) { return true; }
	else return false;	
	}

};

