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
	bool agun;
	
	bool operator == (const Boom& s) const { return (Position == s.Position && timer == s.timer); }
	bool operator != (const Boom& s) const { return !operator==(s); }

	Boom(Vector2f pos, sf::Texture * texture, int size, bool gun) {
		Position = pos;
		
		shape1.setRadius(rand() % ((size + 2) - (size - 2) + 1) + (size - 2));
		
		shape1.setTexture(texture);

			shape1.setRotation(rand() % ((180) - (-180) + 1) + (-180));
			shape1.setOrigin(shape1.getRadius() , shape1.getRadius() );
			shape1.setPosition(pos);
			IntRect Rect(Vector2i(512/4, 0), Vector2i(125, 125));
			
			shape1.setTextureRect(Rect);

		maxtimer = rand() % (6*size - 4*size + 1) + 4*size;
		timer = maxtimer;
		agun = gun;
	}

	void UpdateParticle() {

		if (agun) {
			if (timer == maxtimer - 1)
			{
				IntRect Rect(Vector2i(512 / 2, 0), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 1)
			{
				IntRect Rect(Vector2i((512 / 4) + (512 / 2), 0), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}


			else if (timer == maxtimer - 2)
			{
				IntRect Rect(Vector2i(0, 512 / 4), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 2)
			{
				IntRect Rect(Vector2i(512 / 4, 512 / 4), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 3)
			{
				IntRect Rect(Vector2i(512 / 2, 512 / 4), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 3)
			{
				IntRect Rect(Vector2i((512 / 2) + (512 / 4), 512 / 4), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}

			else if (timer == maxtimer - 4)
			{
				IntRect Rect(Vector2i(0, 512 / 2), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 4)
			{
				IntRect Rect(Vector2i(512 / 4, 512 / 2), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 5)
			{
				IntRect Rect(Vector2i(512 / 2, 512 / 2), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 5)
			{
				IntRect Rect(Vector2i((512 / 2) + (512 / 4), 512 / 2), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}

			else if (timer == maxtimer - 6)
			{
				IntRect Rect(Vector2i(0, (512 / 2) + (512 / 4)), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 6)
			{
				IntRect Rect(Vector2i(512 / 4, (512 / 2) + (512 / 4)), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 7)
			{
				IntRect Rect(Vector2i(512 / 2, (512 / 2) + (512 / 4)), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 7)
			{
				IntRect Rect(Vector2i((512 / 2) + (512 / 4), (512 / 2) + (512 / 4)), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
		}



		else 
		{
			if (timer == maxtimer - 2)
			{
				IntRect Rect(Vector2i(512 / 2, 0), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 4)
			{
				IntRect Rect(Vector2i((512 / 4) + (512 / 2), 0), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}


			else if (timer == maxtimer - 6)
			{
				IntRect Rect(Vector2i(0, 512 / 4), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 8)
			{
				IntRect Rect(Vector2i(512 / 4, 512 / 4), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 10)
			{
				IntRect Rect(Vector2i(512 / 2, 512 / 4), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 12)
			{
				IntRect Rect(Vector2i((512 / 2) + (512 / 4), 512 / 4), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}

			else if (timer == maxtimer - 14)
			{
				IntRect Rect(Vector2i(0, 512 / 2), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 16)
			{
				IntRect Rect(Vector2i(512 / 4, 512 / 2), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 18)
			{
				IntRect Rect(Vector2i(512 / 2, 512 / 2), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 20)
			{
				IntRect Rect(Vector2i((512 / 2) + (512 / 4), 512 / 2), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}

			else if (timer == maxtimer - 22)
			{
				IntRect Rect(Vector2i(0, (512 / 2) + (512 / 4)), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 24)
			{
				IntRect Rect(Vector2i(512 / 4, (512 / 2) + (512 / 4)), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 26)
			{
				IntRect Rect(Vector2i(512 / 2, (512 / 2) + (512 / 4)), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
			else if (timer == maxtimer - 28)
			{
				IntRect Rect(Vector2i((512 / 2) + (512 / 4), (512 / 2) + (512 / 4)), Vector2i(125, 125));

				shape1.setTextureRect(Rect);
			}
		}

		timer -= 1;
	}

};