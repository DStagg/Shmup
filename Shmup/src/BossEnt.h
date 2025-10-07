#pragma once

#include "Entity.h"
#include <SDL3/SDL.h>

class BossEnt : public Entity
{
public:

	BossEnt(Level* lvl);
	~BossEnt();

	void InitTurrets(BasicEnt* ta, BasicEnt* tb);

	void Update(float dt);
	void Draw(SDL_Renderer* renderer);

private:

	BasicEnt* _TurretA;
	BasicEnt* _TurretB;
};