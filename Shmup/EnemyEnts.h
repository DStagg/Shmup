#ifndef ENEMYENTS_H
#define ENEMYENTS_H

#include "Entity.h"
#include "PlayerEnt.h"

class BombEnt : public Entity
{
public:

	BombEnt(Level* level);

	void Update(float dt);

private:

	//Level* _Level;
};

class DroneEnt : public Entity
{
public:

	DroneEnt(Level* lvl);

	void Update(float dt);

private:

	float _ShootTimer = 0.f;
	float _ShootDelay = 1.f;
};



#endif