#include "Entity.h"

Entity::Entity()
{
	SetAlive(true);
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

void Entity::Update(float dt)
{
	GetPresence().UpdatePosition(dt);
	if (_Icon != 0)
	{
		_Icon->Update(dt);
		GetSize().SetSize(_Icon->GetWidth(), _Icon->GetHeight());
	}	
};

void Entity::Draw(sf::RenderWindow* rw)
{
	if (_Icon != 0)
		_Icon->Draw(rw);
};

void Entity::SetIcon(Icon* icon)
{
	_Icon = icon;
};
Icon* Entity::GetIcon()
{
	return _Icon;
};

/////

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