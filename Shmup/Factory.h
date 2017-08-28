#ifndef FACTORY_H
#define FACTORY_H

#include "Entity.h"

#include "PlayerEnt.h"
#include "EnemyEnts.h"

#include "Level.h"

class EntFactory
{
public:

	EntFactory();

	void Init(Level* lvl, ImageManager* img, sf::RenderWindow* rw);

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
	Level* _Level;
};

#endif