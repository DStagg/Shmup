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
	
	Entity* GetPlayer();
	void SetPlayer(Entity* p);

	EntFactory& GetFactory();

private:

	EntList _Enemies;
	EntList _PlayerBullets;
	EntList _EnemyBullets;
	EntList _SFX;
	Entity* _Player;

	EntFactory _Factory;
	Size _Size;
};

#endif