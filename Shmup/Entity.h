#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <algorithm>

#include "AABB.h"
#include "Icon.h"

#include "EntityComponents.h"

class Level;

class Entity
{
public:

	Entity(Level* lvl);
	~Entity();

	Presence& GetPresence();
	Size& GetSize();
	Graphic& GetGraphic();
	Stats& GetStats();

	void SetAlive(bool b);
	bool GetAlive();

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow* rw) = 0;

	void SetLevel(Level* lvl);
	Level* GetLevel();
	
private:

	bool _Alive;

	Presence _Presence;
	Size _Size;
	Stats _Stats;
	Graphic _Graphic;
	
	Level* _Level;
};

class BasicEnt : public Entity
{
public:

	BasicEnt(Level* lvl);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

private:

};

class SFXEnt : public BasicEnt
{
public:

	SFXEnt(Level* lvl);

	void Update(float dt);

private:

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