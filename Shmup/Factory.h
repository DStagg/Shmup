#ifndef FACTORY_H
#define FACTORY_H

#include "Entity.h"

#include "PlayerEnt.h"

class EntFactory
{
public:

	EntFactory();

	void Init(ImageManager* img, sf::RenderWindow* rw);

	enum Types
	{
		Default,
		Player,
		PlayerBullet,
		BombEnemy,
		DroneEnemy,
		SpreaderEnemy,
		SwarmEnemy,
		TankEnemy
	};

	Entity* Spawn(int type, float x, float y);

private:

	ImageManager* _ImgMan;
	sf::RenderWindow* _Window;
};

#endif