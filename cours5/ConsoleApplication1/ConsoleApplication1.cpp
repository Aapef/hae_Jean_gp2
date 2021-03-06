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
#include <SFML/Audio.hpp>

static sf::Shader * simpleShader = nullptr;
float ttime;
float timestamp2 = 0;
int currentminpos = 0;
sf::Vector2f vec(70, 120);
sf::RectangleShape shape(vec);
float rot1 = -90;
float rot2 = -90;
bool p1dead = false;
bool p1wins = false;
bool p2wins = false;
bool p2dead = false;
sf::RectangleShape shape2(vec);
sf::RectangleShape gun(Vector2f(50, 100 * 1.2));
sf::RectangleShape gun2(Vector2f(50 * 1.1, 100 * 1.4));
std::list <Proj> Projectils;
std::list<Boom> Boomlist;
bool p1canshoot = true;
bool p2canshoot = true;
bool shake = false;
int shaker = 0;
bool doplay = false;
int textimer = 0;
bool doflash = false;
int ScoreP1 = 0;
int ScoreP2 = 0;



Vector2f Normalize(Vector2f N) {
	float length = std::sqrt(N.x * N.x + N.y * N.y); 
	N.x /= length;
	N.y /= length;
	return N;
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "A shitty tonk game");
	while (window.isOpen()) {
		rot1 = -90;
		rot2 = -90;
		p1dead = false;
		p2dead = false;
		shaker = 0;
		shake = false;
		p1canshoot = true;
		p2canshoot = true;
		timestamp2 = 0;
		currentminpos = 0;
		shape.setRotation(0);
		shape2.setRotation(0);
		gun.setRotation(0);
		gun2.setRotation(0);
		shape.setFillColor(sf::Color::White);
		shape2.setFillColor(sf::Color::White);
		gun.setFillColor(sf::Color::White);
		gun2.setFillColor(sf::Color::White);

		sf::RectangleShape groundshape(Vector2f(1920,1080));

		sf::Music music;
		if (!music.openFromFile("music.ogg")) { printf("unable to load true soviet music\n"); }
		music.setVolume(35);
		music.setLoop(true);
		music.play();

		sf::SoundBuffer bexplo;
		if (!bexplo.loadFromFile("big explosion.wav")) { printf("unable to load big explosion sound\n"); }

		sf::SoundBuffer sexplo;
		if (!sexplo.loadFromFile("small explosion.wav")) { printf("unable to load small explosion sound\n"); }

		sf::SoundBuffer gunsound;
		if (!gunsound.loadFromFile("Gun.wav")) { printf("unable to load Gun sound\n"); }

		sf::Sound gsound;
		gsound.setBuffer(gunsound);

		sf::Sound ssound;
		ssound.setBuffer(sexplo);

		sf::Sound bsound;
		bsound.setBuffer(bexplo);

		sf::Texture ground;
		if (!ground.loadFromFile("ground.jpg")) { printf("unable to load ground texture\n"); }

		sf::Texture ruin;
		if (!ruin.loadFromFile("ruin.png")) { printf("unable to load ruin texture\n"); }

		groundshape.setTexture(&ground);

		sf::Texture sparks;
		if (!sparks.loadFromFile("sparks.png")) { printf("unable to load sparks texture\n"); }

		sf::Texture explosion;
		if (!explosion.loadFromFile("explosion.png")) { printf("unable to load explosion texture\n"); }

		sf::Texture projtext;
		if (!projtext.loadFromFile("bullet.png")) { printf("unable to load bullet texture\n"); }

		if (!sf::Shader::isAvailable()) {
			printf("no shader available\n");
		}

		simpleShader = new Shader();
		if (!simpleShader->loadFromFile("res/simple.vert", "res/simple.frag")) {
			printf("unable to load shaders\n");
		}

		std::srand(GetTickCount());
		shape.setOrigin(Vector2f(shape.getSize().x / 2, shape.getSize().y / 2 - 10));
		shape2.setOrigin(Vector2f(shape2.getSize().x / 2, shape2.getSize().y / 2 - 5));
		gun.setOrigin(Vector2f(gun.getSize().x / 2, gun.getSize().y / 2 + 30));
		gun2.setOrigin(Vector2f(gun2.getSize().x / 2, gun2.getSize().y / 2 + 40));
		SquareCollider WestWall(-100, 1080, 100, -2000);
		SquareCollider NorthWall(0, -100, 2000, 100);
		SquareCollider EastWall(1900, 1080, 100, -2000);
		SquareCollider SouthWall(0, 1050, 2000, 100);
		SquareCollider CenterWall(1920 / 2 - 200, 1080 / 2 + 200, 400, -400);
		sf::Vector2f vec(400, 400);
		sf::RectangleShape CenterWallShape(vec);
		CenterWallShape.setFillColor(sf::Color::White);
		CenterWallShape.setTexture(&ruin);
		CenterWallShape.setPosition(1920 / 2 - 200, 1080 / 2 - 200);
		Vector2f offset1 = Vector2f(shape.getSize().x / 2, shape.getSize().y / 2 - 10);
		Vector2f offset2 = Vector2f(shape2.getSize().x / 2, shape2.getSize().y / 2 - 5);

		sf::Texture T34Hull;
		if (!T34Hull.loadFromFile("tanks_0_6.png")) {}
		sf::Texture T34Turret;
		if (!T34Turret.loadFromFile("tanks_0_2.png")) {}
		sf::Texture PantherHull;
		if (!PantherHull.loadFromFile("tanks_0_8.png")) {}
		sf::Texture PantherTurret;
		if (!PantherTurret.loadFromFile("tanks_0_4.png")) {}


		sf::Font font2;
		if (!font2.loadFromFile(/*"arial.ttf"*/"Chernobyl.otf"))
		{
			// erreur...
		}

		sf::Font font;
		if (!font.loadFromFile(/*"arial.ttf"*/"Molot.otf"))
		{
			// erreur...
		}

		shape.setPosition(100, 900);
		shape2.setPosition(1720, 100);

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


		sf::RectangleShape flash(Vector2f(1920,1080));
		flash.setFillColor(sf::Color(255, 255, 255, 160));

		Vector2f posbase = window.getView().getCenter();

		auto vieww = window.getView();
		int maxx = posbase.x + 10;
		int minx = posbase.x - 10;
		int maxy = posbase.y + 10;
		int miny = posbase.y - 10;

		while (window.isOpen())
		{
			doflash = false;
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

			if (shake)
			{
				if (shaker <= 5)
				{
					Vector2f vecfzojf(rand() % (maxx - minx + 1) + minx, rand() % (maxy - miny + 1) + miny);
					vieww.setCenter(vecfzojf);
					/*maxx-=0.5f;
					maxy -= 0.5f;
					minx+= 0.5f;
					miny += 0.5f;*/
					shaker++;
				}
				else
				{
					vieww.setCenter(posbase);
					shake = false;
				}
				window.setView(vieww);
			}

			//Mouvements
			if (doplay) {
				if (Joystick::isConnected(0) && !p1dead) {
					if ((sf::Joystick::getAxisPosition(0, Joystick::Y) > 50 || sf::Joystick::getAxisPosition(0, Joystick::Y) < -50) || (sf::Joystick::getAxisPosition(0, Joystick::X) > 50 || sf::Joystick::getAxisPosition(0, Joystick::X) < -50)) {
						float rot11 = 57.3 * atan2(sf::Joystick::getAxisPosition(0, Joystick::X), -sf::Joystick::getAxisPosition(0, Joystick::Y)) - 90;
						//if (gun.getPosition().y > mousepos.y) rot = -rot;
						shape.setRotation(rot11 + 90);

					}
					if (sf::Joystick::getAxisPosition(0, Joystick::Y) > -50)
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
						float rot2 = 57.3 * atan2(sf::Joystick::getAxisPosition(1, Joystick::X), -sf::Joystick::getAxisPosition(1, Joystick::Y)) - 90;
						//if (gun.getPosition().y > mousepos.y) rot = -rot;
						shape2.setRotation(rot2 + 90);

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
						gun.setRotation(rot1 + 90);

					}
					if (sf::Joystick::getAxisPosition(0, Joystick::Z) > 50 && p1canshoot == true)
					{
						p1canshoot = false;
						Vector2f point(cos(rot1 / 57.3) * 100, sin(rot1 / 57.3) * 100);
						Vector2f point1 = shape.getPosition() + point;
						Proj zbleh(point1, point, sf::Color::Green);
						zbleh.shape.setTexture(&projtext);
						Projectils.push_back(zbleh);
						Boom zbleh2(point1 - Vector2f(point.x / 10, point.y / 10), &sparks, 20, true);
						Boomlist.push_back(zbleh2);
						gsound.play();
						
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
						Vector2f point1 = shape2.getPosition() + point;
						Proj zbleh(point1, point, sf::Color::Blue);
						zbleh.shape.setTexture(&projtext);
						Projectils.push_back(zbleh);
						Boom zbleh2(point1-Vector2f(point.x/10, point.y/10), &sparks, 20, true);
						Boomlist.push_back(zbleh2);
						gsound.play();
					}
					else if (sf::Joystick::getAxisPosition(1, Joystick::Z) < 50) p2canshoot = true;
				}
			}

			//Update Colliders

			TankCol.update(shape.getPosition().x - shape.getSize().x / 2.0f, shape.getPosition().y - shape.getSize().y / 2 + 20, shape.getSize().x, shape.getSize().y - 30);
			Tank2Col.update(shape2.getPosition().x - shape2.getSize().x / 2.0f - 10, shape2.getPosition().y - shape2.getSize().y / 2 + 15, shape2.getSize().x + 20, shape2.getSize().y - 20);

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


			gun.setPosition(shape.getPosition());
			gun2.setPosition(shape2.getPosition());
			for (Proj& zbleh : Projectils)
			{
				Vector2f dazonidaz = zbleh.shape.getPosition();
				zbleh.shape.setPosition(zbleh.shape.getPosition() + zbleh.Direction);
				zbleh.updatecollider();
			}

			/*

			//Update Colliders

			TankCol.update(shape.getPosition().x - shape.getSize().x / 2.0f, shape.getPosition().y - shape.getSize().y / 2 + 20, shape.getSize().x, shape.getSize().y - 30);
			Tank2Col.update(shape2.getPosition().x - shape2.getSize().x / 2.0f - 10, shape2.getPosition().y - shape2.getSize().y / 2 + 15, shape2.getSize().x + 20, shape2.getSize().y - 20);



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

*/

			//Proj Bouncing

			for (Proj& zbleh : Projectils)
			{
				if (zbleh.timer == 0) {

					if (NorthWall.CheckCollidingWithSphere(zbleh.collider)) {
						if (zbleh.Life == 1)
						{
							Boom zbleh2(zbleh.shape.getPosition(), &sparks, 30,false);
							Boomlist.push_back(zbleh2);
							Projectils.remove(zbleh);
							shaker = 0;
							shake = true;
							flash.setFillColor(sf::Color(255, 255, 255, 60));
							doflash = true;
							maxx = posbase.x + 5;
							minx = posbase.x - 5;
							maxy = posbase.y + 5;
							miny = posbase.y - 5;

							ssound.play();
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
							Boom zbleh2(zbleh.shape.getPosition(), &sparks, 30, false);
							Boomlist.push_back(zbleh2);
							Projectils.remove(zbleh);
							shaker = 0;
							shake = true;
							flash.setFillColor(sf::Color(255, 255, 255, 60));
							doflash = true;
							maxx = posbase.x + 5;
							minx = posbase.x - 5;
							maxy = posbase.y + 5;
							miny = posbase.y - 5;

							ssound.play();
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
							Boom zbleh2(zbleh.shape.getPosition(), &sparks, 30, false);
							Boomlist.push_back(zbleh2);
							Projectils.remove(zbleh);
							shaker = 0;
							shake = true;
							flash.setFillColor(sf::Color(255, 255, 255, 60));
							doflash = true;
							maxx = posbase.x + 5;
							minx = posbase.x - 5;
							maxy = posbase.y + 5;
							miny = posbase.y - 5;
							ssound.play();
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
							Boom zbleh2(zbleh.shape.getPosition(), &sparks, 30, false);
							Boomlist.push_back(zbleh2);
							Projectils.remove(zbleh);
							shaker = 0;
							shake = true;
							flash.setFillColor(sf::Color(255, 255, 255, 60));
							doflash = true;
							maxx = posbase.x + 5;
							minx = posbase.x - 5;
							maxy = posbase.y + 5;
							miny = posbase.y - 5;
							ssound.play();
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
							Boom zbleh2(zbleh.shape.getPosition(), &sparks, 30, false);
							Boomlist.push_back(zbleh2);
							Projectils.remove(zbleh);
							shaker = 0;
							shake = true;
							flash.setFillColor(sf::Color(255, 255, 255, 60));
							doflash = true;
							maxx = posbase.x + 5;
							minx = posbase.x - 5;
							maxy = posbase.y + 5;
							miny = posbase.y - 5;
							ssound.play();
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

					Boom zbleh2(shape.getPosition(), &explosion, 80, false);
					Boomlist.push_back(zbleh2);
					Boom zbleh3(shape.getPosition(), &sparks, 80, false);
					Boomlist.push_back(zbleh3);
					flash.setFillColor(sf::Color(255, 255, 255, 170));
					doflash = true;
					bsound.play();
					shape.setFillColor(sf::Color::Transparent);
					gun.setFillColor(sf::Color::Transparent);
					p1dead = true;
					if (!p2dead) { p2wins = true;  ScoreP2 += 1; }
					Projectils.remove(zbleh);
					shaker = -50;
					shake = true;
					maxx = posbase.x + 20;
					minx = posbase.x - 20;
					maxy = posbase.y + 20;
					miny = posbase.y - 20;
					break;
				}
				if (Tank2Col.CheckCollidingWithSphere(zbleh.collider) && !p2dead) {
					Boom zbleh2(shape2.getPosition(), &explosion, 80, false);
					Boomlist.push_back(zbleh2);
					Boom zbleh3(shape2.getPosition(), &sparks, 80, false);
					Boomlist.push_back(zbleh3);
					flash.setFillColor(sf::Color(255, 255, 255, 170));
					doflash = true;
					bsound.play();
					shape2.setFillColor(sf::Color::Transparent);
					gun2.setFillColor(sf::Color::Transparent);
					p2dead = true;
					if (!p1dead) { p1wins = true; ScoreP1 += 1; }
					Projectils.remove(zbleh);
					shaker = -50;
					shake = true;
					maxx = posbase.x + 20;
					minx = posbase.x - 20;
					maxy = posbase.y + 20;
					miny = posbase.y - 20;
					break;
				}
				if (zbleh.timer > 0) zbleh.timer = 0;
			}



			//Particles

			for (Boom& zbleh : Boomlist)
			{
				if (zbleh.timer <= zbleh.maxtimer - 30) {
					Boomlist.remove(zbleh);
					break;
				}
				else {

					zbleh.UpdateParticle();
				}
			}



			//Update PrevPos

			TankCol.PrevPos = shape.getPosition();
			Tank2Col.PrevPos = shape2.getPosition(); 

			//Render

			window.draw(groundshape);

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
			}

			if(doflash)window.draw(flash);

			sf::Text text;
			text.setOutlineColor(sf::Color::Black);
			text.setOutlineThickness(2);
			text.setFont(font);
			text.setFillColor(sf::Color(232, 52, 49));
			text.setPosition(750, 800);
			text.setString("Press A to play");
			text.setCharacterSize(50);

			sf::Text text2;
			text2.setOutlineColor(sf::Color::Black);
			text2.setOutlineThickness(2);
			text2.setFont(font);
			text2.setFillColor(sf::Color(232, 52, 49));
			text2.setPosition(730, 900);
			text2.setString("(Player 2 missing)");
			text2.setCharacterSize(50);

			sf::Text Score1;
			Score1.setOutlineColor(sf::Color::Black);
			Score1.setOutlineThickness(2);
			Score1.setFont(font);
			Score1.setFillColor(sf::Color(255, 174, 13));
			Score1.setPosition(20, 20);
			Score1.setString("P1 Score : "+ std::to_string(ScoreP1));
			Score1.setCharacterSize(40);

			sf::Text Score2;
			Score2.setOutlineColor(sf::Color::Black);
			Score2.setOutlineThickness(2);
			Score2.setFont(font);
			Score2.setFillColor(sf::Color(255, 174, 13));
			Score2.setPosition(20, 70);
			Score2.setString("P2 Score : " + std::to_string(ScoreP2));
			Score2.setCharacterSize(40);

			sf::Text title;
			title.setOutlineColor(sf::Color::Black);
			title.setOutlineThickness(2);
			title.setFont(font2);
			title.setFillColor(sf::Color(232, 52, 49));
			title.setPosition(150, 100);
			title.setString("A shitty tonk game");
			title.setCharacterSize(172);


			if (p2wins) 
			{
				title.setPosition(320, 100);
				text.setPosition(740, 800);
				title.setString("Player 2 wins!");
				text.setString("Press Start to restart");
			}
			else if (p1wins) 
			{
				title.setPosition(320, 100);
				text.setPosition(740, 800);
				title.setString("Player 1 wins!");
				text.setString("Press Start to restart");
			}

			window.draw(Score1);
			window.draw(Score2);

			if (!Joystick::isConnected(1))
			{
				if (!doplay && textimer >= 0) window.draw(text2);
			}
			if (!doplay ||(p1dead||p2dead)) window.draw(title);
			if ((!doplay || (p1dead || p2dead) )&& textimer >= 0) window.draw(text);
			if (!doplay && sf::Joystick::isButtonPressed(0, 0)) doplay = true;

			textimer++;

			if (textimer > 15) textimer = -16;
			window.display();

			if (doplay && sf::Joystick::isButtonPressed(0, 7)) { p1wins = false; p2wins = false; Boomlist.clear(); Projectils.clear(); doplay = false; break; }
		}
	}
	
	return 0;
}
