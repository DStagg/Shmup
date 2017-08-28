#include "EntityComponents.h"

//	Size		//

Size::Size(float w, float h)
{
	SetSize(w, h);
};

void Size::SetWidth(float w)
{
	_Width = w;
};
void Size::SetHeight(float h)
{
	_Height = h;
};
void Size::SetSize(float w, float h)
{
	SetWidth(w);
	SetHeight(h);
};

float Size::GetWidth()
{
	return _Width;
};
float Size::GetHeight()
{
	return _Height;
};


//	Presence	//

Presence::Presence(float x, float y, float xv, float yv)
{
	SetPosition(x, y);
	SetVelocity(xv, yv);
};

void Presence::SetX(float x)
{
	_X = x;
};
void Presence::SetY(float y)
{
	_Y = y;
};
void Presence::SetPosition(float x, float y)
{
	SetX(x);
	SetY(y);
};
void Presence::SetXVel(float xv)
{
	_XVel = xv;
};
void Presence::SetYVel(float yv)
{
	_YVel = yv;
};
void Presence::SetVelocity(float xv, float yv)
{
	SetXVel(xv);
	SetYVel(yv);
};

float Presence::GetX()
{
	return _X;
};
float Presence::GetY()
{
	return _Y;
};

float Presence::GetXVel()
{
	return _XVel;
};
float Presence::GetYVel()
{
	return _YVel;
};

void Presence::UpdatePosition(float dt)
{
	SetX(GetX() + GetXVel() * dt);
	SetY(GetY() + GetYVel() * dt);
};