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

	GetPresence().UpdatePosition(dt);
	GetSize().SetSize(GetGraphic().GetCurrentFrame()._Width, GetGraphic().GetCurrentFrame()._Height);
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

	GetPresence().UpdatePosition(dt);
	GetSize().SetSize(GetGraphic().GetCurrentFrame()._Width, GetGraphic().GetCurrentFrame()._Height);
};


//	Spreader	//

SpreaderEnt::SpreaderEnt(Level* lvl) : Entity(lvl)
{
	_ShootTimer = 0.f;
};

void SpreaderEnt::Update(float dt)
{
	_ShootTimer += dt;

	if (_ShootTimer >= _ShootDelay)
	{
		_ShootTimer = 0.f;

		Entity* b1 = GetLevel()->GetFactory().Spawn(EntFactory::EnemyBullet, GetPresence().GetX() + (GetSize().GetWidth() / 2.f), GetPresence().GetY() + GetSize().GetHeight());
		b1->GetPresence().SetXVel(-50.f);
		Entity* b2 = GetLevel()->GetFactory().Spawn(EntFactory::EnemyBullet, GetPresence().GetX() + (GetSize().GetWidth() / 2.f), GetPresence().GetY() + GetSize().GetHeight());
		Entity* b3 = GetLevel()->GetFactory().Spawn(EntFactory::EnemyBullet, GetPresence().GetX() + (GetSize().GetWidth() / 2.f), GetPresence().GetY() + GetSize().GetHeight());
		b3->GetPresence().SetXVel(50.f);

		GetLevel()->GetEnemyBullets().AddEnt(b1);
		GetLevel()->GetEnemyBullets().AddEnt(b2);
		GetLevel()->GetEnemyBullets().AddEnt(b3);
	}

	GetPresence().UpdatePosition(dt);
	GetSize().SetSize(GetGraphic().GetCurrentFrame()._Width, GetGraphic().GetCurrentFrame()._Height);
};


//	Swarm Ent

SwarmEnt::SwarmEnt(Level* lvl) : Entity(lvl)
{
	
};

void SwarmEnt::Update(float dt)
{
	_Timer += dt;
	GetPresence().SetXVel(cos(_Timer)*50.f);
	
	GetPresence().UpdatePosition(dt);
	GetSize().SetSize(GetGraphic().GetCurrentFrame()._Width, GetGraphic().GetCurrentFrame()._Height);
};


//	Tank Ent

TankEnt::TankEnt(Level* lvl) : Entity(lvl)
{

};

void TankEnt::Update(float dt)
{
	_ShootTimer += dt;

	if (_ShootTimer >= _ShootDelay)
	{
		_ShootTimer = 0.f;

		GetLevel()->GetEnemyBullets().AddEnt(GetLevel()->GetFactory().Spawn(EntFactory::EnemyBullet, GetPresence().GetX(), GetPresence().GetY() + GetSize().GetHeight()));
		GetLevel()->GetEnemyBullets().AddEnt(GetLevel()->GetFactory().Spawn(EntFactory::EnemyBullet, GetPresence().GetX() + GetSize().GetWidth(), GetPresence().GetY() + GetSize().GetHeight()));
	}

	GetPresence().UpdatePosition(dt);
	GetSize().SetSize(GetGraphic().GetCurrentFrame()._Width, GetGraphic().GetCurrentFrame()._Height);
};