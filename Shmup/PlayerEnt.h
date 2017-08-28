#ifndef PLAYERENT_H
#define PLAYERENT_H

#include "Entity.h"

class PlayerEnt : public Entity
{
public:

	PlayerEnt(Level* lvl , sf::RenderWindow* rw);

	void Update(float dt);

private:

	sf::RenderWindow* _Window;

};

#endif