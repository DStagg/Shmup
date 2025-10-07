#pragma once

#include "Entity.h"
#include "core/Service.h"

class PlayerEnt : public Entity
{
public:

	PlayerEnt(Level* lvl , SDL_Renderer* renderer);

	void Update(float dt);
	void Draw(SDL_Renderer* renderer);

	float _DoubleShot = 0.f;
	float _Invincibility = 0.f;
	float _Laser = 0.f;
	int _Bombs = 0;

	bool _W = false;
	bool _A = false;
	bool _S = false;
	bool _D = false;
	bool _Space = false;
	bool _B = false;

private:

	SDL_Renderer* _Window;

	float _ShootTimer = 0.f;
	float _ShootDelay = 0.25f;

};