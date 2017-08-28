#include "PlayerEnt.h"

PlayerEnt::PlayerEnt(Level* lvl , sf::RenderWindow* rw) : Entity(lvl)
{
	_Window = rw;
};

void PlayerEnt::Update(float dt)
{
	//	Control Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		GetPresence().SetYVel(-200.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		GetPresence().SetYVel(200.f);
	else
		GetPresence().SetYVel(0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		GetPresence().SetXVel(-200.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		GetPresence().SetXVel(200.f);
	else
		GetPresence().SetXVel(0.f);

	if (GetPresence().GetX() < 0.f)
		GetPresence().SetX(0.f);
	else if (GetPresence().GetX() > _Window->getSize().x - GetSize().GetWidth())
		GetPresence().SetX(_Window->getSize().x - GetSize().GetWidth());

	if (GetPresence().GetY() < 0.f)
		GetPresence().SetY(0.f);

	if (GetStats().GetHP() <= 0)
		SetAlive(false);

	if ((GetStats().GetHP() == 1) && (GetGraphic().GetCurrentAnimName() != "Death"))
		GetGraphic().Swap("Death");

	GetPresence().UpdatePosition(dt);
	GetGraphic().Play(dt);
	GetSize().SetSize((float)GetGraphic().GetCurrentFrame()._Width, (float)GetGraphic().GetCurrentFrame()._Height);

};

void PlayerEnt::Draw(sf::RenderWindow* rw)
{
	GetGraphic().GetSprPntr()->setPosition(GetPresence().GetX(), GetPresence().GetY());
	rw->draw(*GetGraphic().GetSprPntr());
};