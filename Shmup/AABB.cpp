#include "AABB.h"

AABB::AABB()
{
	_X = 0.f;
	_Y = 0.f;
	_Width = 1.f;
	_Height = 1.f;
}

AABB::AABB(float x, float y, float w, float h)
{
	_X = x;
	_Y = y;
	_Width = w;
	_Height = h;
};

AABB::~AABB()
{

};

float AABB::Bottom()
{
	return _Y + _Height - 1.f;
};

float AABB::Right()
{
	return _X + _Width - 1.f;
};

bool AABB::Contains(float x, float y)
{
	if ((x < _X) || (x > Right()))
		return false;
	if ((y < _Y) || (y > Bottom()))
		return false;
	return true;
};

bool AABB::Intersects(AABB box)
{
	if (box.Right() < _X)
		return false;
	if (box._X > Right())
		return false;
	if (box.Bottom() < _Y)
		return false;
	if (box._Y > Bottom())
		return false;
	return true;
};