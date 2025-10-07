#pragma once

#include "Entity.h"
#include "PlayerEnt.h"

#include "core/Utility.h"
#include "core/AABB.h"

class BombEnt : public BasicEnt
{
public:

	BombEnt(Level* level);

	void Update(float dt);

private:

};

class DroneEnt : public BasicEnt
{
public:

	DroneEnt(Level* lvl);

	void Update(float dt);

private:

	float _ShootTimer = 0.f;
	float _ShootDelay = 1.f;
};

class SpreaderEnt : public BasicEnt
{
public:

	SpreaderEnt(Level* lvl);

	void Update(float dt);

private:

	float _ShootTimer = 0.f;
	float _ShootDelay = 1.f;
};

class SwarmEnt : public BasicEnt
{
public:

	SwarmEnt(Level* lvl);

	void Update(float dt);

private:

	float _Timer = 0.f;
};

class TankEnt : public BasicEnt
{
public:

	TankEnt(Level* lvl);

	void Update(float dt);

private:

	float _ShootTimer = 0.f;
	float _ShootDelay = 1.5f;
};