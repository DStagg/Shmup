#include "Entity.h"

Entity::Entity()
{
	SetX(0.f);
	SetY(0.f);
	SetWidth(0.f);
	SetHeight(0.f);
	SetXVel(0.f);
	SetYVel(0.f);
	SetAlive(true);
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

void Entity::SetAlive(bool b)
{
	_Alive = b;
};
bool Entity::GetAlive()
{
	return _Alive;
};

/////

AABB GenBoundBox(Entity* ent)
{
	return GenBoundBox(*ent);
};
AABB GenBoundBox(Entity ent)
{
	return AABB(ent.GetX(), ent.GetY(), ent.GetWidth(), ent.GetHeight());
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


/////

AnimEnt::AnimEnt()
{

};
AnimEnt::~AnimEnt()
{

};

void AnimEnt::SetAnim(Animation a)
{
	_Animation = a;
};
Animation AnimEnt::GetAnim()
{
	return _Animation;
};
Animation* AnimEnt::GetAnimPntr()
{
	return &_Animation;
};