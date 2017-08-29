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
	_SFX.Cull(0);
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
EntList& Level::GetSFX()
{
	return _SFX;
};
EntList& Level::GetPowerups()
{
	return _Powerups;
};
Entity* Level::GetPlayer()
{
	return _Player;
};
Entity* Level::GetLaser()
{
	return _Laser;
};

void Level::SetPlayer(Entity* p)
{
	_Player = p;
};
void Level::SetLaser(Entity* l)
{
	_Laser = l;
};

EntFactory& Level::GetFactory()
{
	return _Factory;
};