#include "Entity.hpp"
#include "Game.hpp"
#include "Particle.h"
#include "FadingParticle.h"

using namespace std;
using namespace sf;
bool docover = false;
int timer = 0;


void Entity::setPosPixel(float pixelX, float pixelY) {
	cx = (int)pixelX / CELL_WIDTH;
	cy = (int)pixelY / CELL_WIDTH;

	rx = (pixelX - (cx*CELL_WIDTH)) / CELL_WIDTH;//reste de cx pour aller a rx
	ry = (pixelY - (cy*CELL_WIDTH)) / CELL_WIDTH;

	syncCoord();
}

void Entity::update(double dt) {
	rx += dx;
	ry += dy;
	///////X BLOCK 
	//maintain X cell coherency
	if (timer >= 60 && getState() == ES_IDLE) docover = true;
	else if(getState() == ES_IDLE) timer++;

	bool cover = false;
	if (docover) {
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				if (willCollide(cx + i, cy + j)) { if (getState() != ES_RUNNING) changeState(ES_COVER); cover = true; }
			}
		}
		if (cover == false && getState() == ES_COVER) changeState(ES_WALKING);
	}

	if (dx > 0) 
		while (rx > 1) { 
			if (!willCollide(cx+1, cy)) {
				rx--;
				cx++;
			}
			else {
				dx = -dx *0.8;
				rx = 0.9;
				break;
			}
		}
	else if (dx < 0) 
		while (rx < 0) { 
			if (!willCollide(cx - 1, cy)) {
				rx++;
				cx--;
			}
			else {
				dx = -dx * 0.8;
				rx = 0.1;
				break;
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
			if (!willCollide(cx, cy - 1)) { ry++; cy--; }
			else
			{
				dy = -dy * 0.8; ry = 0.1; break;
			}
		}
	}

	dx *= 0.8;
	dy *= 0.8;
	if (abs(dx) < 0.05) dx = 0;
	if (abs(dy) < 0.05) dy = 0;

	if( (dx == 0) && (dy == 0) && getState() != ES_IDLE && getState() != ES_COVER) {
		changeState( ES_IDLE );
		docover = false;
		timer = 0;
	}

	syncCoord();
}

void Entity::dropParticles() {
	int life = 30;
	float sp = Lib::rd() + 0.5;
	auto & g = *Game::me;

	float rdx = Lib::rd() * 6;
	float rdy = Lib::rd() * 6 - 8;
	{
		auto c = new CircleShape(8, 64);
		c->setOrigin(8, 8);
		c->setPosition(pixelX + rdx,pixelY + rdy);
		c->setFillColor(sf::Color(0xE580EB1a));
		auto p = new FadingParticle(c);
		p->life = 30;
		p->speed.y = sp;
		p->bhv = Particle::applySpeed;
		g.pvec.push_back(p);

	}

	{
		auto c = new CircleShape(2, 32);
		c->setOrigin(2, 2);
		c->setPosition(pixelX+rdx, pixelY+rdy);
		c->setFillColor(sf::Color(0xE580EBff));

		auto p = new FadingParticle(c);
		p->life = 30;
		p->speed.y = sp;
		p->bhv = Particle::applySpeed;
		g.pvec.push_back(p);
	}
}

void Entity::draw(sf::RenderWindow & win) {

	sf::Text coords;
	coords.setFont(*Game::me->fnt);
	coords.setPosition(pixelX + 20, pixelY - 20);
	coords.setFillColor(sf::Color::Red);
	coords.setString(
		std::to_string(cx) + "," + std::to_string(cy)
		+ " " + std::to_string(rx) + ","+std::to_string(ry)
		+ " "+ getStateName() );

	win.draw(*spr);
	//win.draw(coords);
}

void Entity::changeState(EntityState nes)
{
	EntityState oldState = state;

	switch (oldState)
	{
	default:
		break;
	}

	switch (nes)
	{
	default:
		break;
	}

	state = nes;
}

bool Entity::willCollide(int cx, int cy)
{
	return Game::me->willCollide(this, cx, cy);
}

std::string Entity::getStateName() {
	switch (state)
	{
	case ES_IDLE:
		spr->setFillColor(sf::Color::White);
		return "idle";
		break;
	case ES_RUNNING:
		spr->setFillColor(sf::Color::Green);
		docover = false;
		return "run";
		break;
	case ES_COVER:
		docover = true;
		spr->setFillColor(sf::Color::Blue);
		return "cover";
		break;
	case ES_WALKING:
		docover = true;
		spr->setFillColor(sf::Color::Red);
		return "walk";
		break;
	}
}
