#pragma once
#include <math.h>
#include "Lib.hpp"
#include "Collider.hpp"
#include <SFML/Graphics.hpp>

class Proj {

public:
	Vector2f Direction;
	int timer = 0;
	int Life;
	Vector2f Position;
	CircleShape shape;
	SphereCollider collider = SphereCollider(Vector2f(0,0),1);

	bool operator == (const Proj& s) const { return Position == s.Position; }
	bool operator != (const Proj& s) const { return !operator==(s); }

	Proj(Vector2f Coordinates, Vector2f Forces, sf::Color color) 
	{
		Life = 2;
		collider.Update(Coordinates, 10);
		shape.setRadius(10);
		shape.setFillColor(color);
		shape.setPosition(Coordinates);
		Position = Coordinates;
		Direction = Vector2f(Forces.x/10, Forces.y/10);
	}

	~Proj() 
	{
		//delete this;
	}

	void updatecollider() 
	{
		Position = shape.getPosition();
		collider.Update(shape.getPosition(), 10);
	}

};
