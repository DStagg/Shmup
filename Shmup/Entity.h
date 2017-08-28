#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <algorithm>

#include "AABB.h"
#include "Icon.h"

#include "EntityComponents.h"

class Entity
{
public:

	Entity();
	~Entity();

	Presence& GetPresence();
	Size& GetSize();

	void SetAlive(bool b);
	bool GetAlive();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow* rw);

	void SetIcon(Icon* icon);
	Icon* GetIcon();
	
private:

	bool _Alive;

	Presence _Presence;
	Size _Size;
	Icon* _Icon;
	
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

#endif