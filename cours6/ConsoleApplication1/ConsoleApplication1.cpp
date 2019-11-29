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

float timestamp2 = 0;
Vector2i F1(100,100);
Vector2i F2(200, 200);
Vector2i F3(300, 300);
Vector2i F4(400, 400);
Vector2i F5(500, 500);
Vector2i F6(600, 600);
Vector2i F7(700, 700);
int currentminpos = 0;
sf::Vector2f vec(100, 100);
sf::RectangleShape shape(vec);
sf::Vector2i projs;

void DrawCurve(sf::RenderWindow &win, float timestamp)
{
	sf::VertexArray va(sf::LineStrip);
	sf::Color red = sf::Color(255, 0, 0, 255);
	sf::Color blue = sf::Color(0, 255, 0, 255);
	int nb = 1920;

	float stride = 1280.0 / (nb);

	std::vector<Vector2f> points;

	for (int j = 0; j < 8; j++) 
	{
		Vector2f v(j * 100, j * 100);
		if (j == 1) { v.x = F1.x; v.y = F1.y;
		}
		if (j == 3) { v.x = F3.x; v.y = F3.y;
		}
		if (j == 5) { v.x = F5.x; v.y = F5.y;
		}
		if (j == 7) { v.x = F7.x; v.y = F7.y;
		}
		if (j == 2) {
			v.x = F2.x; v.y = F2.y;
		}
		if (j == 4) {
			v.x = F4.x; v.y = F4.y;
		}
		if (j == 6) {
			v.x = F6.x; v.y = F6.y;
		}
		points.push_back(v);
	}
	float doo = true;
	for (int i = 0; i < nb + 1; ++i) {
		double ratio = 1.0 * i / nb;
		double x = 0.0;
		double y = 0.0;
		sf::Color c = sf::Color::Red;


		Vector2f pos = Lib::plot2(ratio, points);
		x = pos.x;
		y = pos.y;
		sf::Vertex vertex(Vector2f(x, y), c);
		va.append(vertex);
		
		if (ratio >= timestamp && doo == true) {
			doo = false;
			CircleShape shapee(10);
			shapee.setFillColor(sf::Color::Green);
			shapee.setPosition(Vector2f(x, y));
			win.draw(shapee);
			
		}
		if (timestamp2 >= 1) timestamp2 = 0;
	}
	win.draw(va);

}

void RenderProjs() 
{
	/*for each(Vector2i ver in projs) 
	{
		;
	}*/
}

int main()
{
	bool dojump = false;
	sf::Font font;
	sf::Texture text;

	if (!sf::Shader::isAvailable()) {
		printf("no shader available\n");
	}

	if (! text.loadFromFile("res/tanks_0_6.png")) {
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

		//DrawCurve(window, timestamp2);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
		{
			//projs.add(shape.getPosition().x + 50, shape.getPosition().y + 50);
		}

		RenderProjs();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) /*&& dojump == false*/) 
		{
			/*dojump = true;
			timer = 0;*/
			shape.move(0, -5);
		}
		/*if (dojump) {
			shape.setPosition(shape.getPosition().x,-(((-(1 / 2)*(-9.8f)*(timer*timer)/400) + (100 * std::sin(0.45/2 * timer)))-800));
			timer = timer + 1;
			if (timer == 20) dojump = false;
		}*/
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
		window.display();

		simpleShader->setUniform("time", ttime);
		ttime = ttime + 0.1f;
		/*sf::Text textou;		
		sf::Time f = clocky.getElapsedTime();
		float ff = f.asMicroseconds();
		float i = 1000000/ ff;
		textou.setFont(font);
		textou.setString("FPS : " + std::to_string(i));
		textou.setCharacterSize(24);
		textou.setFillColor(sf::Color::Red);
		window.clear();
		window.draw(textou);
		window.display();*/

		if (Keyboard::isKeyPressed(sf::Keyboard::F1)) {
			F1 = sf::Mouse::getPosition(window);
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::F2)) {
			F2 = sf::Mouse::getPosition(window);
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::F3)) {
			F3 = sf::Mouse::getPosition(window);
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::F4)) {
			F4 = sf::Mouse::getPosition(window);
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::F5)) {
			F5 = sf::Mouse::getPosition(window);
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::F6)) {
			F6 = sf::Mouse::getPosition(window);
		}
		if (Keyboard::isKeyPressed(sf::Keyboard::F7)) {
			F7 = sf::Mouse::getPosition(window);
		}

	}

	return 0;
}
