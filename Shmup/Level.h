#ifndef LEVEL_H
#define LEVEL_H

#include "Entity.h"
#include "Factory.h"

class Level
{
public:

	Level(float w = 0.f, float h = 0.f);
	~Level();

	Size& GetSize();
	EntList& GetEnemies();
	EntList& GetPlayerBullets();
	EntList& GetEnemyBullets();
	EntList& GetSFX();
	EntList& GetPowerups();
	
	Entity* GetPlayer();
	Entity* GetBoss();
	Entity* GetLaser();
	void SetPlayer(Entity* p);
	void SetBoss(Entity* b);
	void SetLaser(Entity* e);

	EntFactory& GetFactory();

private:

	EntList _Enemies;
	EntList _PlayerBullets;
	EntList _EnemyBullets;
	EntList _SFX;
	EntList _Powerups;
	Entity* _Player;
	Entity* _Boss;
	Entity* _Laser;

	EntFactory _Factory;
	Size _Size;
};

#endif