#ifndef FACTORY_H
#define FACTORY_H

#include "Entity.h"

class EntFactory
{
public:

	EntFactory();

	void Init(ImageManager* img);

	enum Types
	{
		Default,
		Player,
		PlayerBullet,
		BombEnemy
	};

	Entity* Spawn(int type, float x, float y);

private:

	ImageManager* _ImgMan;
};

#endif