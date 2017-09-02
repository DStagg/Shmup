#ifndef BOSSENT_H
#define BOSSENT_H

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

#endif