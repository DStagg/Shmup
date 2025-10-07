#pragma once

#include "Entity.h"

#include "PlayerEnt.h"
#include "EnemyEnts.h"
#include "BossEnt.h"

class Level;

class EntFactory
{
public:

	EntFactory();

	void Init(Level* lvl, ImageManager* img, SDL_Renderer* renderer);

	enum Types
	{
		Default,
		Player,
		PlayerBullet,
		BombEnemy,
		DroneEnemy,
		SpreaderEnemy,
		SwarmEnemy,
		TankEnemy,
		EnemyBullet,
		Boss,
		DoublePowerup,
		LaserPowerup,
		BombPowerup,
		HealPowerup,
		InvinciblePowerup,
		Laser,
		Explosion
	};

	Entity* Spawn(int type, float x, float y);

private:

	ImageManager* _ImgMan;
	SDL_Renderer* _Window;
	Level* _Level;
};