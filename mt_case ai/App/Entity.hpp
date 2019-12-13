#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;


enum EntityState {
	ES_IDLE,
	ES_RUNNING,
	ES_WALKING,
	ES_COVER
};

class Entity {
public:
	const static int CELL_WIDTH = 16; // taille de chaque case width

	int cx = 0;
	int cy = 0;

	float rx = 0.5f;
	float ry = 0.5f;

	float dx = 0.0f;
	float dy = 0.0f;

	float gy = 0.03f;

	float pixelX = 0.0;
	float pixelY = 0.0;

	bool applyGravity = false;

	sf::Shape * spr;

	Entity( sf::Shape * spr ) {
		this->spr = spr;
	}

	void setPos(float crx, float cry) {
		rx += crx;
		ry += crx;
	}

	void setPosPixel(float pixelX, float pixelY);

	void update(double dt);

	void dropParticles();

	void updatecontrols(double dt) 
	{
		float lat_acc = 0.075;
		float max_lat_speed = 0.75;
		/*if (getState() == ES_WALKING ) {
		max_lat_speed = 0.15;
		}*/


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
				dx += lat_acc;
				if (dx > max_lat_speed) dx = max_lat_speed;
				if (getState() == ES_IDLE || getState() == ES_COVER || getState() == ES_WALKING) changeState(ES_RUNNING);
			}
			else
			{
				max_lat_speed = 0.15;
				dx += lat_acc;
				if (dx > max_lat_speed) dx = max_lat_speed;
				if (getState() == ES_IDLE  || getState() == ES_RUNNING) changeState(ES_WALKING);
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
				dx -= lat_acc;
				if (dx < -max_lat_speed) dx = -max_lat_speed;
				if (getState() == ES_IDLE || getState() == ES_COVER || getState() == ES_WALKING) changeState(ES_RUNNING);
			}
			else 
			{
				max_lat_speed = 0.15;
				dx -= lat_acc;
				if (dx < -max_lat_speed) dx = -max_lat_speed;
				if (getState() == ES_IDLE ||  getState() == ES_RUNNING) changeState(ES_WALKING);
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
				dy += lat_acc;
				if (dy > max_lat_speed) dy = max_lat_speed;
				if (getState() == ES_IDLE || getState() == ES_COVER || getState() == ES_WALKING) changeState(ES_RUNNING);
			}
			else
			{
				max_lat_speed = 0.15;
				dy += lat_acc;
				if (dy > max_lat_speed) dy = max_lat_speed;
				if (getState() == ES_IDLE ||  getState() == ES_RUNNING) changeState(ES_WALKING);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
				dy -= lat_acc;
				if (dy < -max_lat_speed) dy = -max_lat_speed;
				if (getState() == ES_IDLE || getState() == ES_COVER || getState() == ES_WALKING) changeState(ES_RUNNING);
			}
			else
			{
				max_lat_speed = 0.15;
				dy -= lat_acc;
				if (dy < -max_lat_speed) dy = -max_lat_speed;
				if (getState() == ES_IDLE ||  getState() == ES_RUNNING) changeState(ES_WALKING);
			}
		}

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			setPosPixel(100, 600);
			dx = dy = 0.0f;
			applyGravity = false;
			changeState(ES_IDLE);
		}*/

		update(dt);
	}

	void syncCoord() {
		pixelX = cx * CELL_WIDTH + rx * CELL_WIDTH;
		pixelY = cy * CELL_WIDTH + ry * CELL_WIDTH;
		spr->setPosition(pixelX, pixelY );
	}

	void draw(sf::RenderWindow & win);

	EntityState getState() { return state; };
	void		changeState(EntityState nes);

	bool		willCollide(int cx, int cy);

	std::string getStateName();

private:
	EntityState	state = ES_IDLE;
};
