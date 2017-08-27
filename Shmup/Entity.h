#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <algorithm>

#include "AABB.h"
#include "Icon.h"

#include "ImageManager.h"

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

	void SetAlive(bool b);
	bool GetAlive();

	void DoUpdate(float dt);
	void DoDraw(sf::RenderWindow* rw);

	void SetIcon(Icon* icon);
	Icon* GetIcon();
	
private:

	virtual void Update(float dt) = 0;

	Icon* _Icon;

	float _X, _Y;
	float _Width, _Height;
	float _XVel, _YVel;
	bool _Alive;
};

AABB GenBoundBox(Entity* ent);

class EntList
{
public:

	EntList();
	~EntList();

	void AddEnt(Entity* ent);
	void DelEnt(Entity* ent);
	void Cull(int limit);

	int CountEnts();
	Entity* GetEnt(int i);

private:

	std::vector<Entity*> _Entities;
};

class AnimEnt : public Entity
{
public:

	AnimEnt(std::string textag);
	~AnimEnt();

	void SetAnim(Animation a);
	Animation GetAnim();
	Animation* GetAnimPntr();

	void SetTexTag(std::string textag);
	std::string GetTexTag();

	void Update(float dt);

private:

	Animation _Animation;
	std::string _TexTag;
};

#endif