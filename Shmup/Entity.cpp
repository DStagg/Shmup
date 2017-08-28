#include "Entity.h"

Entity::Entity(Level* lvl)
{
	SetAlive(true);
	SetLevel(lvl);
}
Entity::~Entity()
{

};

Presence& Entity::GetPresence()
{
	return _Presence;
};

Size& Entity::GetSize()
{
	return _Size;
};

Graphic& Entity::GetGraphic()
{
	return _Graphic;
};

Stats& Entity::GetStats()
{
	return _Stats;
};

void Entity::SetAlive(bool b)
{
	_Alive = b;
};
bool Entity::GetAlive()
{
	return _Alive;
};

void Entity::SetLevel(Level* lvl)
{
	_Level = lvl;
};
Level* Entity::GetLevel()
{
	return _Level;
};

/////


//	BasicEnt	//

BasicEnt::BasicEnt(Level* lvl) : Entity(lvl)
{

};

void BasicEnt::Update(float dt)
{
	GetPresence().UpdatePosition(dt);
	GetGraphic().Play(dt);
	GetSize().SetSize((float)GetGraphic().GetCurrentFrame()._Width, (float)GetGraphic().GetCurrentFrame()._Height);
};

void BasicEnt::Draw(sf::RenderWindow* rw)
{
	GetGraphic().GetSprPntr()->setPosition(GetPresence().GetX(), GetPresence().GetY());
	rw->draw(*GetGraphic().GetSprPntr());
};


//	SFXEnt		//

SFXEnt::SFXEnt(Level* lvl) : BasicEnt(lvl)
{

};

void SFXEnt::Update(float dt)
{
	BasicEnt::Update(dt);
	if ((GetGraphic().GetCurrentAnim()._CurrentFrame == (int)GetGraphic().GetCurrentAnim()._Frames.size() - 1) && (GetGraphic().GetCurrentAnim()._Time > GetGraphic().GetCurrentFrame()._FrameTime))
		SetAlive(false);
};

//////////

AABB GenBoundBox(Entity* ent)
{
	return AABB(ent->GetPresence().GetX(), ent->GetPresence().GetY(), ent->GetSize().GetWidth(), ent->GetSize().GetHeight());
};

/////

EntList::EntList()
{

};
EntList::~EntList()
{
	Cull(0);
};

void EntList::AddEnt(Entity* ent)
{
	if (ent == 0)
		return;
	if (std::find(_Entities.begin(), _Entities.end(), ent) != _Entities.end())
		return;
	_Entities.push_back(ent);
};
void EntList::DelEnt(Entity* ent)
{
	if (ent == 0)
		return;
	if (std::find(_Entities.begin(), _Entities.end(), ent) != _Entities.end())
	{
		delete ent;
		_Entities.erase(std::find(_Entities.begin(), _Entities.end(), ent));
	}
};
void EntList::Cull(int limit)
{
	if (limit < 0)
		return;

	while (CountEnts() > limit)
	{
		delete GetEnt(0);
		_Entities.erase(_Entities.begin());
	}

	for (int i = 0; i < CountEnts(); i++)
	{
		if (!GetEnt(i)->GetAlive())
		{
			delete GetEnt(i);
			_Entities.erase(_Entities.begin() + i);
			i--;
		}
	}
};

int EntList::CountEnts()
{
	return (int)_Entities.size();
};
Entity* EntList::GetEnt(int i)
{
	if (i < 0)
		i = 0;
	if (i >= CountEnts())
		i = CountEnts() - 1;

	return _Entities[i];
};
