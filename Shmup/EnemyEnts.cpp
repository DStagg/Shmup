#include "EnemyEnts.h"
#include "Level.h"

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
};