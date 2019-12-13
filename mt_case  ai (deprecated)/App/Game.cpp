#include "Game.hpp"
#include "Entity.hpp"

Entity * player;

bool canjump = true;

void Game::update(double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		player->dx += 0.075;
		if (player->dx > 0.75) player->dx = 0.75;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		player->dx -= 0.075;
		if (player->dx < -0.75) player->dx = -0.75;
	}
	
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  ) 
	{	
		player->dy += 0.075;
		if (player->dy > 0.75) player->dy = 0.75;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		player->dy -= 0.075;
		if (player->dy < -0.75) player->dy = -0.75;
	}

	for (auto it = evec.begin(); it != evec.end();) {
		Entity * ent = *it;
		ent->update(dt);
		it++;
	}
}

void Game::init() {
	RectangleShape *sh = new RectangleShape(Vector2f(12, 24));
	sh->setFillColor(sf::Color::Magenta);
	sh->setOrigin(6, 24);
	Entity * ent = new Entity(sh);
	ent->setPosPixel(100, 100);
	evec.push_back(ent);
	player = ent;
	playe = ent;
	Entity e = *playe;
	e.ge = this;
}

void Game::draw(RenderWindow & win)
{
	for (auto it = evec.begin(); it != evec.end();) {
		Entity * ent = *it;
		ent->draw(win);
		it++;
	}

	Entity e = *playe;
	auto CW = e.CX_W;
	RectangleShape cell;
	cell.setFillColor(sf::Color(0x918EF0ff));
	cell.setSize(Vector2f(CW, CW));
	for (Vector2i & pl : platforms) {
		cell.setPosition(pl.x * CW, pl.y * CW);
		win.draw(cell);
	}

	for (auto it = pvec.begin(); it != pvec.end();) {
		Particle * p = *it;
		p->update();
		if (p->killed) {
			it = pvec.erase(it);
		}
		else {
			p->draw(win);
			it++;
		}
	}

	/*RectangleShape line(Vector2f(1000, 1));
	line.setPosition(100, 100);
	line.setFillColor(sf::Color::Green);
	win.draw(line);*/
}
