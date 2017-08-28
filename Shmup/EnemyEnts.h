#ifndef ENEMYENTS_H
#define ENEMYENTS_H

#include "Entity.h"
#include "PlayerEnt.h"

#include "Utility.h"

class BombEnt : public Entity
{
public:

	BombEnt(Level* level);

	void Update(float dt);

private:

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

class SpreaderEnt : public Entity
{
public:

	SpreaderEnt(Level* lvl);

	void Update(float dt);

private:

	float _ShootTimer = 0.f;
	float _ShootDelay = 1.f;
};

class SwarmEnt : public Entity
{
public:

	SwarmEnt(Level* lvl);

	void Update(float dt);

private:

	float _Timer = 0.f;
};

class TankEnt : public Entity
{
public:

	TankEnt(Level* lvl);

	void Update(float dt);

private:

	float _ShootTimer = 0.f;
	float _ShootDelay = 1.5f;
};

#endif