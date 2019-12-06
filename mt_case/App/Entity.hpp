#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

enum EntityState {
	ES_IDLE,
	ES_RUNNING,
	ES_JUMPING,

};

class Entity {
public:

	EntityState curstate = ES_IDLE;

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
		if (dy > 0)
		{
			while (ry > 1) {
				if (!willCollide(cx, cy + 1)) { ry--; cy++; }
				else
				{
					dy = 0; ry = 0.9; curstate = ES_IDLE; break;
					
				}
			}
		}
		
		if (dy < 0) 
		{
			while (ry < 0)
			{
				if (!willCollide(cx, cy - 1)) { ry++; cy--; }
				else
				{
					dy = -dy * 0.8; ry = 0.1; break;
				}
			}
		}
		

		dx *= 0.92;
		if (dy < 0) { dy *= 0.9; dy += 0.02; }
		if (dy > 0) { dy *= 1.02; dy += 0.05; }
		if (dy > 5) dy = 5;
		if (abs(dx) < 0.05) dx = 0;

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
