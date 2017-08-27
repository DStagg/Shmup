#ifndef SHMUPENTS_H
#define SHMUPENTS_H

#include "Entity.h"

class PlayerEnt : public Entity
{
public:

	PlayerEnt();
	
private:

	void Update(float dt);

};

#endif