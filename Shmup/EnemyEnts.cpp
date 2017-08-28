#include "EnemyEnts.h"
#include "Level.h"

//	Bomb		//

BombEnt::BombEnt(Level* lvl) : BasicEnt(lvl)
{
	
};

void BombEnt::Update(float dt)
{
	AABB kill_box(GetPresence().GetX() - 50.f, GetPresence().GetY() - 50.f, 100.f + GetSize().GetWidth(), 100.f + GetSize().GetHeight());
	AABB warn_box(GetPresence().GetX() - 100.f, GetPresence().GetY() - 100.f, 200.f + GetSize().GetWidth(), 200.f + GetSize().GetHeight());
	
	if (GetAlive() && warn_box.Intersects(GenBoundBox(GetLevel()->GetPlayer())) && (GetGraphic().GetCurrentAnimName() != "Armed"))
		GetGraphic().Swap("Armed");
	else if (GetAlive() && !warn_box.Intersects(GenBoundBox(GetLevel()->GetPlayer())) && (GetGraphic().GetCurrentAnimName() == "Armed"))
		GetGraphic().Swap("Idle");
	else if (GetAlive() && kill_box.Intersects(GenBoundBox(GetLevel()->GetPlayer())))
	{
		SetAlive(false);
		GetGraphic().Swap("Death");
		GetLevel()->GetPlayer()->GetStats().Hurt(1);
		GetLevel()->GetSFX().AddEnt(GetLevel()->GetFactory().Spawn(EntFactory::Explosion, GetPresence().GetX(), GetPresence().GetY()));
	}

	BasicEnt::Update(dt);
};



//	Drone		//

DroneEnt::DroneEnt(Level* lvl) : BasicEnt(lvl)
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

	BasicEnt::Update(dt);
};


//	Spreader	//

SpreaderEnt::SpreaderEnt(Level* lvl) : BasicEnt(lvl)
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

	BasicEnt::Update(dt);
};


//	Swarm Ent

SwarmEnt::SwarmEnt(Level* lvl) : BasicEnt(lvl)
{
	
};

void SwarmEnt::Update(float dt)
{
	if (_Timer == 0.f)
	{
		if (GetPresence().GetX() < 100.f)
			GetPresence().SetX(100.f);
		else if (GetPresence().GetX() > GetLevel()->GetSize().GetWidth() - (100.f + GetSize().GetWidth()))
			GetPresence().SetX(GetLevel()->GetSize().GetWidth() - (100.f + GetSize().GetWidth()));
	}

	_Timer += dt;
	GetPresence().SetXVel(cos(_Timer)*50.f);
	
	BasicEnt::Update(dt);
};



//	Tank Ent

TankEnt::TankEnt(Level* lvl) : BasicEnt(lvl)
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

	BasicEnt::Update(dt);
};



