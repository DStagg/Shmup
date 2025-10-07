#pragma once

#include "Entity.h"

class BossEnt : public Entity
{
public:

	BossEnt(Level* lvl);
	~BossEnt();

	void InitTurrets(BasicEnt* ta, BasicEnt* tb);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

private:

	BasicEnt* _TurretA;
	BasicEnt* _TurretB;
};