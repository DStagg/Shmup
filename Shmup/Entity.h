#ifndef ENTITY_H
#define ENTITY_H

#include "AABB.h"

class Entity
{
public:

	Entity();
	~Entity();

	void SetX(float x);
	void SetY(float y);
	void SetPosition(float x, float y);
	void SetWidth(float w);
	void SetHeight(float h);
	void SetSize(float w, float h);
	void SetXVel(float xv);
	void SetYVel(float yv);
	void SetVelocity(float xv, float yv);

	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();
	float GetXVel();
	float GetYVel();



private:

	float _X, _Y;
	float _Width, _Height;
	float _XVel, _YVel;

};

AABB GenBoundBox(Entity* ent);
AABB GenBoundBox(Entity ent);

#endif