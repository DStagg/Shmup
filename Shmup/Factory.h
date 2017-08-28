#ifndef FACTORY_H
#define FACTORY_H

#include "Entity.h"

class EntFactory
{
public:

	EntFactory();

	Entity* Spawn(std::string type, float x, float y);
};

#endif