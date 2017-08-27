#include "Entity.h"

Entity::Entity()
{
	SetX(0.f);
	SetY(0.f);
	SetWidth(0.f);
	SetHeight(0.f);
	SetXVel(0.f);
	SetYVel(0.f);
}
Entity::~Entity()
{

};

void Entity::SetX(float x)
{
	_X = x;
};
void Entity::SetY(float y)
{
	_Y = y;
};
void Entity::SetPosition(float x, float y)
{
	SetX(x);
	SetY(y);
};

void Entity::SetWidth(float w)
{
	_Width = w;
};
void Entity::SetHeight(float h)
{
	_Height = h;
};
void Entity::SetSize(float w, float h)
{
	SetWidth(w);
	SetHeight(h);
};

void Entity::SetXVel(float xv)
{
	_XVel = xv;
};
void Entity::SetYVel(float yv)
{
	_YVel = yv;
};
void Entity::SetVelocity(float xv, float yv)
{
	SetXVel(xv);
	SetYVel(yv);
};

float Entity::GetX()
{
	return _X;
};
float Entity::GetY()
{
	return _Y;
};
float Entity::GetWidth()
{
	return _Width;
};
float Entity::GetHeight()
{
	return _Height;
};
float Entity::GetXVel()
{
	return _XVel;
};
float Entity::GetYVel()
{
	return _YVel;
};

AABB GenBoundBox(Entity* ent)
{
	return GenBoundBox(*ent);
};
AABB GenBoundBox(Entity ent)
{
	return AABB(ent.GetX(), ent.GetY(), ent.GetWidth(), ent.GetHeight());
};