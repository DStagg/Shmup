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


//	Graphic

Graphic::Graphic()
{
	
};
Graphic::Graphic(sf::Sprite spr)
{

};

void Graphic::AddAnimation(std::string tag, Animation anim)
{
	_Animations[tag] = anim;
};

void Graphic::Play(float dt)
{
	if (GetCurrentAnimName() == "Static")
		return;
	
	GetCurrentAnim().Play(dt);
	_Sprite.setTextureRect(sf::IntRect(GetCurrentFrame()._X, GetCurrentFrame()._Y, GetCurrentFrame()._Width, GetCurrentFrame()._Height));
};

void Graphic::Swap(std::string tag)
{
	GetCurrentAnim()._CurrentFrame = 0;
	GetCurrentAnim()._Time = 0.f;

	_CurrentAnim = tag;

	if ( tag == "Static" )
		_Sprite.setTextureRect(sf::IntRect(0,0,_Sprite.getTexture()->getSize().x, _Sprite.getTexture()->getSize().y));
}

std::string Graphic::GetCurrentAnimName()
{
	return _CurrentAnim;
};
Animation& Graphic::GetCurrentAnim()
{
	return _Animations[GetCurrentAnimName()];
};
AnimationFrame Graphic::GetCurrentFrame()
{
	if (GetCurrentAnimName() == "Static")
		return AnimationFrame(0, 0, _Sprite.getTexture()->getSize().x, _Sprite.getTexture()->getSize().y, 0.f);
	return _Animations[GetCurrentAnimName()].GetCurrFrame();
};

void Graphic::SetSprite(sf::Sprite spr)
{
	_Sprite = spr;
};

sf::Sprite* Graphic::GetSprPntr()
{
	return &_Sprite;
};




//	Stats		//

Stats::Stats(int hp)
{
	SetHP(hp);
	SetMaxHP(hp);
};

void Stats::SetHP(int hp)
{
	_CurrentHP = hp;
};
int Stats::GetHP()
{
	return _CurrentHP;
};

void Stats::SetMaxHP(int hp)
{
	_MaximumHP = hp;
};
int Stats::GetMaxHP()
{
	return _MaximumHP;
};

void Stats::Hurt(int hp)
{
	SetHP(GetHP() - hp);
};