#include "pch.h"
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <sstream>
#include <SFML/System/FileInputStream.hpp>
#include <math.h>
#include "Lib.hpp"

float ttime = 0.0f;
static sf::Shader * simpleShader = nullptr;
static sf::Shader * redShader = nullptr;
static sf::Shader * bloomShader = nullptr;
static sf::Shader * blurShader = nullptr;

class Turtle : public sf::ConvexShape 
{
public : 
	sf::Transform m_Trs;
	Turtle() : sf::ConvexShape(3) 
	{
		setFillColor(sf::Color(255, 200, 50));
		setOutlineThickness(2);
		setOutlineColor(sf::Color(30, 30, 30));

		setPoint(0, Vector2f(-24, 0));
		setPoint(1, Vector2f(24, -16));
		setPoint(2, Vector2f(24, 16));
	}

	void setTransform(sf::Transform trs) {
		m_Trs = trs;
	}
};

static sf::Transform s_Initial;
static std::vector<sf::Transform> s_Trs;
static std::vector<Turtle*> s_Turtles;

static void startTransforms() {
	s_Initial = Transform::Identity;
	s_Initial.translate(64, 64);
	s_Initial.rotate(180);
}

static void translateX(float dx) {
	sf::Transform res;
	res.translate(dx, 0);
	s_Trs.push_back(res);
}

static void translateY(float dy) {
	sf::Transform res;
	res.translate(0, dy);
	s_Trs.push_back(res);
}

static void rotate(float d) {
	sf::Transform res;
	res.rotate(d);
	s_Trs.push_back(res);
}

static void scaleX(float dx) {
	sf::Transform res;
	res.scale(dx, dx);
	s_Trs.push_back(res);
}

static void scaleY(float dy) {
	sf::Transform res;
	res.scale(dy, dy);
	s_Trs.push_back(res);
}

static void computeTransform(sf::Transform & result, int step = -1) {
	sf::Transform inter;
	inter.combine(s_Initial);
	if (step <= -1) {
		for (sf::Transform t : s_Trs) {
			inter = inter.combine(t);
		}
	}
	else {
		step--;
		for (sf::Transform t : s_Trs) {
			inter = inter.combine(t);
			if(step <=0)break;
		}
	}
	result = inter;
}

void plotTurtle() 
{
	sf::Transform cur;
	computeTransform(cur, s_Trs.size() - 1);
	Turtle* t = new Turtle();
	t->setTransform(cur);
	s_Turtles.push_back(t);
}

float timestamp2 = 0;
int currentminpos = 0;
sf::Vector2f vec(100, 100);
sf::RectangleShape shape(vec);
sf::Vector2i projs;


int main()
{
	bool dojump = false;
	sf::Font font;
	sf::Texture text;
	if (!sf::Shader::isAvailable()) {
		printf("no shader available\n");
	}

	if (!text.loadFromFile("res/tanks_0_6.png")) {
		printf("failed to load texture");
	}
	shape.setTexture(&text);
	simpleShader = new Shader();
	if (!simpleShader->loadFromFile("res/simple.vert", "res/simple.frag")) {
		printf("unable to load shaders\n");
	}

	if (!font.loadFromFile("arial.ttf"))
	{
		// erreur...
	}
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");


	shape.setPosition(0, 900);
	shape.setFillColor(sf::Color::White);

	sf::Clock clocky;
	sf::Time appStart = clocky.getElapsedTime();
	window.setVerticalSyncEnabled(true);
	float timestamp = 0;
	int timer = 0;
	int io = 1;

	startTransforms();
	plotTurtle();

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
				switch (event.type)
				{
						case sf::Event::KeyReleased:
						{
							if (event.key.code == sf::Keyboard::Space)
								{
								startTransforms();

								sf::Transform trs;
								computeTransform(trs);

								for (Turtle *t : s_Turtles) delete t;
								s_Turtles.clear();

								Turtle* t = new Turtle();
								t->setTransform(trs);
								s_Turtles.push_back(t);
							}
							auto delta = 32;
							if (event.key.code == sf::Keyboard::F1) { translateX(delta); plotTurtle(); }
							if (event.key.code == sf::Keyboard::F2) { translateX(-delta); plotTurtle(); }
							if (event.key.code == sf::Keyboard::F3) { rotate(180); plotTurtle(); }
							if (event.key.code == sf::Keyboard::F4) { rotate(45); plotTurtle(); }
							if (event.key.code == sf::Keyboard::F6) { scaleX(0.5); plotTurtle(); }
							if (event.key.code == sf::Keyboard::F7) { scaleX(2.0); plotTurtle(); }
							if (event.key.code == sf::Keyboard::F8) { scaleY(0.5); plotTurtle(); }
							if (event.key.code == sf::Keyboard::F9) { scaleY(2.0); plotTurtle(); }
						}
				}
		}
		window.clear();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{

			shape.move(0, -5);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			shape.move(0, 5);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			shape.move(-2, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			shape.move(2, 0);
		}
		window.draw(shape, simpleShader);
		for (Turtle *i : s_Turtles) {
			window.draw(*i, i->m_Trs);
		}
		window.display();

		simpleShader->setUniform("time", ttime);
		ttime = ttime + 0.1f;
		
	}
	return 0;
}
