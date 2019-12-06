#include "pch.h"
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <sstream>
#include <SFML/System/FileInputStream.hpp>
#include <math.h>
#include <list>
#include "Lib.hpp"
#include "Collider.hpp"
#include "Proj.hpp"
#include "Particle.h"
#include <windows.h>

float timestamp2 = 0;
int currentminpos = 0;
sf::Vector2f vec(70, 120);
sf::RectangleShape shape(vec);
float rot1;
float rot2;
bool p1dead = false;
bool p2dead = false;
sf::RectangleShape shape2(vec);
sf::RectangleShape gun(Vector2f(50, 100 * 1.2));
sf::RectangleShape gun2(Vector2f(50 * 1.1, 100 * 1.4));
std::list <Proj> Projectils;
std::list<Boom> Boomlist;
bool p1canshoot = true;
bool p2canshoot = true;



Vector2f Normalize(Vector2f N) {
	float length = std::sqrt(N.x * N.x + N.y * N.y); 
	N.x /= length;
	N.y /= length;
	return N;
}



int main()
{
	std::srand(GetTickCount());
	shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y / 2 - 10));
	shape2.setOrigin(Vector2f(shape2.getSize().x / 2, shape2.getSize().y / 2 - 5));
	gun.setOrigin(Vector2f(gun.getSize().x/2, gun.getSize().y / 2 + 30));
	gun2.setOrigin(Vector2f(gun2.getSize().x / 2, gun2.getSize().y / 2 +40));
	SquareCollider WestWall(-100, 1080, 100, -2000);
	SquareCollider NorthWall(0, -100, 2000, 100);
	SquareCollider EastWall(1900, 1080, 100, -2000);
	SquareCollider SouthWall(0, 1050, 2000, 100);
	SquareCollider CenterWall(1920/2 -200, 1080/2 +200, 400, -400);
	sf::Vector2f vec(400, 400);
	sf::RectangleShape CenterWallShape(vec);
	CenterWallShape.setFillColor(sf::Color::White);
	CenterWallShape.setPosition(1920 / 2 - 200, 1080 / 2 - 200);
	Vector2f offset1 = Vector2f(shape.getSize().x / 2, shape.getSize().y / 2 - 10);
	Vector2f offset2 = Vector2f(shape2.getSize().x / 2, shape2.getSize().y / 2 - 5);

	sf::Texture T34Hull;
	if (!T34Hull.loadFromFile("tanks_0_6.png")){}
	sf::Texture T34Turret;
	if (!T34Turret.loadFromFile("tanks_0_2.png")) {}
	sf::Texture PantherHull;
	if (!PantherHull.loadFromFile("tanks_0_8.png")) {}
	sf::Texture PantherTurret;
	if (!PantherTurret.loadFromFile("tanks_0_4.png")) {}


	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// erreur...
	}
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
	
	shape.setPosition(100, 900);
	shape2.setPosition(1720, 100);
	/*gun.setFillColor(sf::Color::Red);
	gun2.setFillColor(sf::Color::Red);
	shape.setFillColor(sf::Color::Green);
	shape2.setFillColor(sf::Color::Blue);*/

	shape.setTexture(&T34Hull);
	shape2.setTexture(&PantherHull);
	gun.setTexture(&T34Turret);
	gun2.setTexture(&PantherTurret);

	sf::Clock clocky;
	sf::Time appStart = clocky.getElapsedTime();
	window.setVerticalSyncEnabled(true);
	float timestamp = 0;
	int timer = 0;
	int io = 1;
	SquareCollider TankCol(shape.getPosition().x, shape.getPosition().y, shape.getSize().x, shape.getSize().y - 10);
	TankCol.PrevPos = shape.getPosition();

	SquareCollider Tank2Col(shape2.getPosition().x, shape2.getPosition().y, shape2.getSize().x, shape2.getSize().y - 10);
	Tank2Col.PrevPos = shape2.getPosition();

	while (window.isOpen())
	{
		if (timestamp <= 0 && io == -1) io = 1;
		if (timestamp >= 250 / 50 && io == 1) io = -1;
		timestamp += io * 0.05;
		timestamp2 += 0.01;
		
		clocky.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		
		}
		window.clear();



		//Mouvements

		if (Joystick::isConnected(0) && !p1dead) {
			if ((sf::Joystick::getAxisPosition(0, Joystick::Y) > 50 || sf::Joystick::getAxisPosition(0, Joystick::Y) < -50) || (sf::Joystick::getAxisPosition(0, Joystick::X) > 50 || sf::Joystick::getAxisPosition(0, Joystick::X) < -50)) {
				rot1 = 57.3 * atan2(sf::Joystick::getAxisPosition(0, Joystick::X), -sf::Joystick::getAxisPosition(0, Joystick::Y)) - 90;
				//if (gun.getPosition().y > mousepos.y) rot = -rot;
				shape.setRotation(rot1 + 90);

			}
			if (sf::Joystick::getAxisPosition(0,Joystick::Y)>-50)
			{
				shape.move(0, 4);
			}
			if (sf::Joystick::getAxisPosition(0, Joystick::Y) < 50)
			{
				shape.move(0, -4);
			}
			if (sf::Joystick::getAxisPosition(0, Joystick::X) > -50)
			{
				shape.move(4, 0);
			}
			if (sf::Joystick::getAxisPosition(0, Joystick::X) < 50)
			{
				shape.move(-4, 0);
			}
		}

		if (Joystick::isConnected(1) && !p2dead) {
			if ((sf::Joystick::getAxisPosition(1, Joystick::Y) > 50 || sf::Joystick::getAxisPosition(1, Joystick::Y) < -50) || (sf::Joystick::getAxisPosition(1, Joystick::X) > 50 || sf::Joystick::getAxisPosition(1, Joystick::X) < -50)) {
				rot1 = 57.3 * atan2(sf::Joystick::getAxisPosition(1, Joystick::X), -sf::Joystick::getAxisPosition(1, Joystick::Y)) - 90;
				//if (gun.getPosition().y > mousepos.y) rot = -rot;
				shape2.setRotation(rot1 + 90);

			}
			if (sf::Joystick::getAxisPosition(1, Joystick::Y) > -50)
			{
				shape2.move(0, 4);
			}
			if (sf::Joystick::getAxisPosition(1, Joystick::Y) < 50)
			{
				shape2.move(0, -4);
			}
			if (sf::Joystick::getAxisPosition(1, Joystick::X) > -50)
			{
				shape2.move(4, 0);
			}
			if (sf::Joystick::getAxisPosition(1, Joystick::X) < 50)
			{
				shape2.move(-4, 0);
			}
		}



		//Ciblage

		/*Vector2i mousepos = sf::Mouse::getPosition(window);

		float rot = 57.3 *(std::acos((mousepos.x - gun.getPosition().x) / (std::sqrt(((mousepos.y - gun.getPosition().y)*(mousepos.y - gun.getPosition().y)) + ((mousepos.x - gun.getPosition().x)*(mousepos.x - gun.getPosition().x))))));
		*/


		if (Joystick::isConnected(0) && !p1dead) {

			if ((sf::Joystick::getAxisPosition(0, Joystick::U) > 50 || sf::Joystick::getAxisPosition(0, Joystick::U) < -50) || (sf::Joystick::getAxisPosition(0, Joystick::V) > 50 || sf::Joystick::getAxisPosition(0, Joystick::V) < -50)) {
				rot1 = 57.3 * atan2(sf::Joystick::getAxisPosition(0, Joystick::U), -sf::Joystick::getAxisPosition(0, Joystick::V)) - 90;
				//if (gun.getPosition().y > mousepos.y) rot = -rot;
				gun.setRotation(rot1 + 90);

			}
			if (sf::Joystick::getAxisPosition(0, Joystick::Z)> 50 && p1canshoot == true)
			{
				p1canshoot = false;
				Vector2f point(cos(rot1 / 57.3) * 100, sin(rot1 / 57.3) * 100);
				Vector2f point1 = shape.getPosition() /*+ Vector2f(40, 40)*/ + point;
				Proj zbleh(point1, point, sf::Color::Green);
				Projectils.push_back(zbleh);
			}
			else if (sf::Joystick::getAxisPosition(0, Joystick::Z) < 50) p1canshoot = true;
		}

		if (Joystick::isConnected(1) && !p2dead) {

			if ((sf::Joystick::getAxisPosition(1, Joystick::U) > 50 || sf::Joystick::getAxisPosition(1, Joystick::U) < -50) || (sf::Joystick::getAxisPosition(1, Joystick::V) > 50 || sf::Joystick::getAxisPosition(1, Joystick::V) < -50)) {
				rot2 = 57.3 * atan2(sf::Joystick::getAxisPosition(1, Joystick::U), -sf::Joystick::getAxisPosition(1, Joystick::V)) - 90;
				gun2.setRotation(rot2 + 90);

			}
			if (sf::Joystick::getAxisPosition(1, Joystick::Z) > 50 && p2canshoot == true)
			{
				p2canshoot = false;
				Vector2f point(cos(rot2 / 57.3) * 100, sin(rot2 / 57.3) * 100);
				Vector2f point1 = shape2.getPosition() /*+ Vector2f(40, 40)*/ + point;
				Proj zbleh(point1, point, sf::Color::Blue);
				Projectils.push_back(zbleh);
			}
			else if (sf::Joystick::getAxisPosition(1, Joystick::Z) < 50) p2canshoot = true;
		}

		//gun.setPosition(Vector2f(shape.getPosition().x + shape.getSize().x/2, shape.getPosition().y + shape.getSize().y/2 -10));
		//gun2.setPosition(Vector2f(shape2.getPosition().x + shape2.getSize().x/2, shape2.getPosition().y + shape2.getSize().y/2 ));
		gun.setPosition(shape.getPosition());
		gun2.setPosition(shape2.getPosition());
		for (Proj& zbleh : Projectils)
		{
			Vector2f dazonidaz = zbleh.shape.getPosition();
			zbleh.shape.setPosition(zbleh.shape.getPosition() + zbleh.Direction);
			zbleh.updatecollider();
		}



		//Update Colliders

		TankCol.update(shape.getPosition().x - shape.getSize().x/2.0f, shape.getPosition().y - shape.getSize().y / 2 + 20, shape.getSize().x, shape.getSize().y - 30);
		Tank2Col.update(shape2.getPosition().x - shape2.getSize().x/2.0f - 10 , shape2.getPosition().y - shape2.getSize().y / 2 + 15, shape2.getSize().x + 20, shape2.getSize().y - 20);



		//Collision Check

		if (NorthWall.CheckColliding(TankCol))shape.setPosition(TankCol.PrevPos);
		if (SouthWall.CheckColliding(TankCol))shape.setPosition(TankCol.PrevPos);
		if (EastWall.CheckColliding(TankCol))shape.setPosition(TankCol.PrevPos);
		if (WestWall.CheckColliding(TankCol))shape.setPosition(TankCol.PrevPos);
		if (CenterWall.CheckColliding(TankCol))shape.setPosition(TankCol.PrevPos);

		if (NorthWall.CheckColliding(Tank2Col))shape2.setPosition(Tank2Col.PrevPos);
		if (SouthWall.CheckColliding(Tank2Col))shape2.setPosition(Tank2Col.PrevPos);
		if (EastWall.CheckColliding(Tank2Col))shape2.setPosition(Tank2Col.PrevPos);
		if (WestWall.CheckColliding(Tank2Col))shape2.setPosition(Tank2Col.PrevPos);
		if (CenterWall.CheckColliding(Tank2Col))shape2.setPosition(Tank2Col.PrevPos);



		//Proj Bouncing

		for (Proj& zbleh : Projectils)
		{
			if (zbleh.timer == 0) {

				if (NorthWall.CheckCollidingWithSphere(zbleh.collider)) {
					if (zbleh.Life == 1)
					{
						Boom zbleh2(zbleh.shape.getPosition(), sf::Color::Yellow, 10);
						Boomlist.push_back(zbleh2);
						Projectils.remove(zbleh);
						break;
					}
					else if (zbleh.Life >= 2)
					{
						zbleh.timer = 1;
						zbleh.Life -= 1;
						float y = 0;
						float x = 1;
						Vector2f n(y, x);
						if (NorthWall.GetAngleOfCollision(zbleh.collider) == 0)n = Vector2f(x, y);
						Vector2f u = (((zbleh.Direction.x* n.x) + (zbleh.Direction.y* n.y)) / ((n.x* n.x) + (n.y* n.y))) * n;
						Vector2f w = zbleh.Direction - u;
						zbleh.Direction = w - u;
					}
				}
				


				if (SouthWall.CheckCollidingWithSphere(zbleh.collider)) {
					if (zbleh.Life == 1)
					{
						Boom zbleh2(zbleh.shape.getPosition(), sf::Color::Yellow, 10);
						Boomlist.push_back(zbleh2);
						Projectils.remove(zbleh);
						break;
					}
					else if (zbleh.Life >= 2)
					{
						zbleh.timer = 1;
						zbleh.Life -= 1;
						float y = 0;
						float x = 1;
						Vector2f n(y, x);
						if (SouthWall.GetAngleOfCollision(zbleh.collider) == 0)n = Vector2f(x, y);
						Vector2f u = (((zbleh.Direction.x* n.x) + (zbleh.Direction.y* n.y)) / ((n.x* n.x) + (n.y* n.y))) * n;
						Vector2f w = zbleh.Direction - u;
						zbleh.Direction = w - u;
					}
				}



				if (EastWall.CheckCollidingWithSphere(zbleh.collider)) {
					if (zbleh.Life == 1)
					{
						Boom zbleh2(zbleh.shape.getPosition(), sf::Color::Yellow, 10);
						Boomlist.push_back(zbleh2);
						Projectils.remove(zbleh);
						break;
					}
					else if (zbleh.Life >= 2)
					{
						zbleh.timer = 1;
						zbleh.Life -= 1;
						float y = 0;
						float x = 1;
						Vector2f n(y, x);
						if (EastWall.GetAngleOfCollision(zbleh.collider) == 0) n = Vector2f(x, y);
						Vector2f u = (((zbleh.Direction.x* n.x) + (zbleh.Direction.y* n.y)) / ((n.x* n.x) + (n.y* n.y))) * n;
						Vector2f w = zbleh.Direction - u;
						zbleh.Direction = w - u;
					}
				}



				if (WestWall.CheckCollidingWithSphere(zbleh.collider)) {
					if (zbleh.Life == 1)
					{
						Boom zbleh2(zbleh.shape.getPosition(), sf::Color::Yellow, 10);
						Boomlist.push_back(zbleh2);
						Projectils.remove(zbleh);
						break;
					}
					else if (zbleh.Life >= 2)
					{
						zbleh.timer = 1;
						zbleh.Life -= 1;
						float y = 0;
						float x = 1;
						Vector2f n(y, x);
						if (WestWall.GetAngleOfCollision(zbleh.collider) == 0)n = Vector2f(x, y);
						Vector2f u = (((zbleh.Direction.x* n.x) + (zbleh.Direction.y* n.y)) / ((n.x* n.x) + (n.y* n.y))) * n;
						Vector2f w = zbleh.Direction - u;
						zbleh.Direction = w - u;
					}
				}

				if (CenterWall.CheckCollidingWithSphere(zbleh.collider)) {
					if (zbleh.Life == 1)
					{
						Boom zbleh2(zbleh.shape.getPosition(), sf::Color::Yellow, 10);
						Boomlist.push_back(zbleh2);
						Projectils.remove(zbleh);
						break;
					}
					else if (zbleh.Life >= 2)
					{
						zbleh.timer = 1;
						zbleh.Life -= 1;
						float y = 0;
						float x = 1;
						Vector2f n(y, x);
						if (CenterWall.GetAngleOfCollision(zbleh.collider) == 0)n = Vector2f(x, y);
						Vector2f u = (((zbleh.Direction.x* n.x) + (zbleh.Direction.y* n.y)) / ((n.x* n.x) + (n.y* n.y))) * n;
						Vector2f w = zbleh.Direction - u;
						zbleh.Direction = w - u;
					}
				}

			}
			else zbleh.timer = zbleh.timer + 1;

			if (TankCol.CheckCollidingWithSphere(zbleh.collider) && !p1dead) {
				
				Boom zbleh2(shape.getPosition(), sf::Color::Red, 20);
				Boomlist.push_back(zbleh2);
				Boom zbleh3(shape.getPosition(), sf::Color::Red, 20);
				Boomlist.push_back(zbleh3);

				shape.setFillColor(sf::Color::Transparent);
				gun.setFillColor(sf::Color::Transparent);
				p1dead = true;
				Projectils.remove(zbleh);
				break;
			}
			if (Tank2Col.CheckCollidingWithSphere(zbleh.collider) && !p2dead) {
				Boom zbleh2(shape2.getPosition(), sf::Color::Red, 20);
				Boomlist.push_back(zbleh2);
				Boom zbleh3(shape2.getPosition(), sf::Color::Red, 20);
				Boomlist.push_back(zbleh3);
				
				shape2.setFillColor(sf::Color::Transparent);
				gun2.setFillColor(sf::Color::Transparent);
				p2dead = true;
				Projectils.remove(zbleh);
				break;
			}
			if (zbleh.timer > 0) zbleh.timer = 0;
		}



		//Particles

		for (Boom& zbleh : Boomlist)
		{			
			if (zbleh.timer <= 0) {
				Boomlist.remove(zbleh);
				break;
			}
			else { 
				
				zbleh.UpdateParticle();
			}
		}



		//Update PrevPos

		TankCol.PrevPos = shape.getPosition();//- Vector2f(-50,50);
		Tank2Col.PrevPos = shape2.getPosition(); //- Vector2f(-50, 50);



		//Render
		
		for (Proj zbleh : Projectils)
		{
			window.draw(zbleh.shape);
		}

		window.draw(shape);
		window.draw(shape2);
		window.draw(gun);
		window.draw(gun2);
		window.draw(CenterWallShape);
		for (Boom zbleh : Boomlist) {
			window.draw(zbleh.shape1);
			window.draw(zbleh.shape2);
			window.draw(zbleh.shape3);
			window.draw(zbleh.shape4);
		}
		window.display();
	}

	return 0;
}
