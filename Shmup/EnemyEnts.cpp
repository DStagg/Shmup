#include "EnemyEnts.h"
#include "Level.h"

//	Bomb		//

BombEnt::BombEnt(Level* lvl) : Entity(lvl)
{
	
};

void BombEnt::Update(float dt)
{
	AABB box(GetPresence().GetX() - 50.f, GetPresence().GetY() - 50.f, 100.f + GetSize().GetWidth(), 100.f + GetSize().GetHeight());
	if (box.Intersects(GenBoundBox(GetLevel()->GetPlayer())))
	{
		GetLevel()->GetPlayer()->GetStats().Hurt(1);
		SetAlive(false);
	}

	Entity::Update(dt);
	GetSize().SetSize(GetIcon()->GetWidth(), GetIcon()->GetHeight());
};


//	Drone		//

DroneEnt::DroneEnt(Level* lvl) : Entity(lvl)
{
	_ShootTimer = 0.f;
};

void DroneEnt::Update(float dt)
{
	_ShootTimer += dt;

	if (_ShootTimer >= _ShootDelay)
	{
		_ShootTimer = 0.f;

		GetLevel()->GetEnemyBullets().AddEnt(GetLevel()->GetFactory().Spawn(EntFactory::EnemyBullet, GetPresence().GetX() + (GetSize().GetWidth() / 2.f), GetPresence().GetY() + GetSize().GetHeight()));
	}

	Entity::Update(dt);
	GetSize().SetSize(GetIcon()->GetWidth(), GetIcon()->GetHeight());
};