#ifndef AABB_H
#define AABB_H

class AABB
{
public:

	AABB();
	AABB(float x, float y, float w, float h);	//	Defines an axis-aligned bounding box with top-left (x,y) and dimensions (w,h)
	~AABB();

	float Right();
	float Bottom();

	float _X, _Y, _Width, _Height;

	bool Contains(float x, float y);
	bool Intersects(AABB box);
};

#endif