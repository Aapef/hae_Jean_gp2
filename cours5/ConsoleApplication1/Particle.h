#pragma once
#include <math.h>
#include "Lib.hpp"
#include <SFML/Graphics.hpp>

class Boom {

public:
	int timer;
	int maxtimer;
	CircleShape shape1;
	CircleShape shape2;
	CircleShape shape3;
	CircleShape shape4;
	Vector2f Position;


	bool operator == (const Boom& s) const { return (Position == s.Position && timer == s.timer); }
	bool operator != (const Boom& s) const { return !operator==(s); }

	Boom(Vector2f pos, sf::Color color, int size) {
		Position = pos;
		
		shape1.setRadius(rand() % ((size + 2) - (size - 2) + 1) + (size - 2));
		shape1.setPosition(pos + Vector2f(rand() % (2 - (-2) + 1) + (-2), rand() % (2 - (-2) + 1) + (-2)));
		shape1.setFillColor(color);

		shape2.setRadius(rand() % ((size + 2) - (size - 2) + 1) + (size - 2));
		shape2.setPosition(pos + Vector2f(rand() % (2 - (-2) + 1) + (-2), rand() % (2 - (-2) + 1) + (-2)));
		shape2.setFillColor(color);

		shape3.setRadius(rand() % ((size + 2) - (size - 2) + 1) + (size - 2));
		shape3.setPosition(pos + Vector2f(rand() % (2 - (-2) + 1) + (-2), rand() % (2 - (-2) + 1) + (-2)));
		shape3.setFillColor(color);

		shape4.setRadius(rand() % ((size + 2) - (size - 2) + 1) + (size - 2));
		shape4.setPosition(pos + Vector2f(rand() % (2 - (-2) + 1) + (-2), rand() % (2 - (-2) + 1) + (-2)));
		shape4.setFillColor(color);

		maxtimer = rand() % (6*size - 4*size + 1) + 4*size;
		timer = maxtimer;
	}

	void UpdateParticle() {

		shape1.move(Vector2f((float)maxtimer/100.0f, 0));
		shape1.setRadius(shape1.getRadius() - 5.0f/(float)maxtimer);
		shape2.move(Vector2f(-(float)maxtimer / 100.0f, 0));
		shape2.setRadius(shape1.getRadius() - 5.0f / (float)maxtimer);
		shape3.move(Vector2f(0, (float)maxtimer / 100.0f));
		shape3.setRadius(shape1.getRadius() - 5.0f / (float)maxtimer);
		shape4.move(Vector2f(0, -(float)maxtimer / 100.0f));
		shape4.setRadius(shape1.getRadius() - 5.0f / (float)maxtimer);

		timer -= 1;
	}

};