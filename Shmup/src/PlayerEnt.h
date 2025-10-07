#pragma once

#include "Entity.h"
#include "Service.h"

class PlayerEnt : public Entity
{
public:

	PlayerEnt(Level* lvl , sf::RenderWindow* rw);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	float _DoubleShot = 0.f;
	float _Invincibility = 0.f;
	float _Laser = 0.f;
	int _Bombs = 0;

private:

	sf::RenderWindow* _Window;

	float _ShootTimer = 0.f;
	float _ShootDelay = 0.25f;

};