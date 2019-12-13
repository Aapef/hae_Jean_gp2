#pragma once

#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;

enum EntityState {
	ES_IDLE,
	ES_RUNNING,
	ES_WALKING,
	ES_COVER,

};

class Entity {
public:
	
	EntityState curstate = ES_IDLE;
	Game *ge;

	int CX_W = 16;
	int CX_H = 16;

	bool canjump = true;

	int cx = 0;
	int cy = 0;

	float rx = 0.5f;
	float ry = 0.5f;

	float dx = 0.0f;
	float dy = 0.0f;

	float pixelX = 0.0f;
	float pixelY = 0.0f;

	sf::Shape * spr;

	Entity( sf::Shape * spr ) {
		this->spr = spr;
	}

	void togglePlatform(int cx, int cy) 
	{
		Game g = *ge;
		for (auto it = g.platforms.begin(); it != g.platforms.end(); it++) {
			Vector2i & pl = *it;
			if (pl.x == cx && pl.y == cy) {
				g.platforms.erase(it);
				return;
			}
		}
		g.platforms.push_back(Vector2i(cx, cy));
	}

	void setPos(float crx, float cry) {
		rx += crx;
		ry += cry;
	}

	void updateCollision()
	{

	}

	bool willCollide(int cx, int cy)
	{	
		int screenw = 1280 / CX_W;
		int screenh = 720 / CX_H;

		if (cx < 0) return true;
		else if (cx >= screenw ) return true;

		if (cy < 0) return true;
		else if (cy >= screenh) return true;

		return false;
	}

	void setPosPixel(float nx, float ny) {
		cx = nx / 16;
		cy = ny / 16;

		rx = (nx - (int)(cx*CX_W)) / CX_W;
		ry = (ny - (int)(cy*CX_H)) / CX_H;

		syncCoord();
	}

	void update(double dt)
	{
		rx += dx;
		ry += dy;
		if (dx > 0) {
			while (rx > 1) 
			{ 
				if (!willCollide(cx + 1, cy)) { rx--; cx++; } 
				else 
				{
					dx = -dx * 0.8; rx = 0.9; break;
				}
			}
		}
		if (dx < 0) {
			while (rx < 0) 
			{
				if (!willCollide(cx - 1, cy)) { rx++; cx--; }
				else
				{
					dx = -dx * 0.8; rx = 0.1; break;
				}
			}
		}
		if (dy > 0) {
			while (ry > 1)
			{
				if (!willCollide(cx, cy + 1)) { ry--; cy++; }
				else
				{
					dy = -dy * 0.8; ry = 0.9; break;
				}
			}
		}
		if (dy < 0) {
			while (ry < 0)
			{
				if (!willCollide(cx, cy-1)) { ry++; cy--; }
				else
				{
					dy = -dy * 0.8; ry = 0.1; break;
				}
			}
		}


		dx *= 0.92;
		dy *= 0.92;
		if (abs(dx) < 0.05) dx = 0;
		if (abs(dy) < 0.05) dy = 0;

		syncCoord();
	}

	void syncCoord() 
	{
		
		pixelX = cx * CX_W + rx * CX_W;
		pixelY = cy * CX_H + ry * CX_H;
		spr->setPosition(pixelX, pixelY);

	}

	void draw(sf::RenderWindow & win) {
		win.draw(*spr);
	}

	void changeState(EntityState state) {
		EntityState oldstate = state;

		switch (oldstate) 
		{
		default: break;
		}

		switch (state) 
		{
		default: break;
		}
		curstate = state;
	}
};
