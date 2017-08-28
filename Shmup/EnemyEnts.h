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

	Level* _Level;
};





#endif