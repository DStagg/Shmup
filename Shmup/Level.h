#ifndef LEVEL_H
#define LEVEL_H

#include "Entity.h"

class Level
{
public:

	Level(float w = 0.f, float h = 0.f);
	~Level();

	Size& GetSize();
	EntList& GetEnemies();
	EntList& GetPlayerBullets();
	EntList& GetEnemyBullets();
	
	Entity* GetPlayer();
	void SetPlayer(Entity* p);

private:

	EntList _Enemies;
	EntList _PlayerBullets;
	EntList _EnemyBullets;

	Entity* _Player;

	Size _Size;
};

#endif