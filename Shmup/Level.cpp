#include "Level.h"

Level::Level(float w, float h)
{
	GetSize().SetSize(w, h);
}

Level::~Level()
{
	delete _Player;
	_Enemies.Cull(0);
	_PlayerBullets.Cull(0);
	_EnemyBullets.Cull(0);
};

Size& Level::GetSize()
{
	return _Size;
};
EntList& Level::GetEnemies()
{
	return _Enemies;
};
EntList& Level::GetPlayerBullets()
{
	return _PlayerBullets;
};
EntList& Level::GetEnemyBullets()
{
	return _EnemyBullets;
};
Entity* Level::GetPlayer()
{
	return _Player;
}
void Level::SetPlayer(Entity* p)
{
	_Player = p;
};