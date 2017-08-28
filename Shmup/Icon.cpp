#include "Icon.h"
#include "Entity.h"

Icon::Icon(Entity* ent)
{
	_Entity = ent;
};

/////

SpriteIcon::SpriteIcon(Entity* ent, sf::Sprite spr) : Icon(ent)
{
	_Sprite = spr;
};

void SpriteIcon::Update(float dt)
{
	_Sprite.setPosition(_Entity->GetPresence().GetX(), _Entity->GetPresence().GetY());
};

void SpriteIcon::Draw(sf::RenderWindow* rw)
{
	rw->draw(_Sprite);
};

float SpriteIcon::GetWidth()
{
	return _Sprite.getLocalBounds().width;
};
float SpriteIcon::GetHeight()
{
	return _Sprite.getLocalBounds().height;
};

/////

AnimIcon::AnimIcon(Entity* ent, sf::Sprite spr, Animation anim) : Icon(ent)
{
	_Sprite = spr;
	_Animation = anim;
};

void AnimIcon::Update(float dt)
{
	_Animation.Play(dt);
	_Sprite.setPosition(_Entity->GetPresence().GetX(), _Entity->GetPresence().GetY());
	_Sprite.setTextureRect(AnimIntRect(_Animation));

};

void AnimIcon::Draw(sf::RenderWindow* rw)
{
	rw->draw(_Sprite);
};

float AnimIcon::GetWidth()
{
	return (float)_Animation.GetCurrFrame()._Width;
};

float AnimIcon::GetHeight()
{
	return (float)_Animation.GetCurrFrame()._Height;
};

/////

RectIcon::RectIcon(Entity* ent, sf::Color col) : Icon(ent)
{
	_Rectangle.setOutlineColor(col);
	_Rectangle.setOutlineThickness(1.f);
	_Rectangle.setFillColor(sf::Color(0, 0, 0, 0));
	_Rectangle.setSize(sf::Vector2f(0.f, 0.f));
};

void RectIcon::Update(float dt)
{
	_Rectangle.setPosition(_Entity->GetPresence().GetX(), _Entity->GetPresence().GetY());
	_Rectangle.setSize(sf::Vector2f(_Entity->GetSize().GetWidth(), _Entity->GetSize().GetHeight()));
};

void RectIcon::Draw(sf::RenderWindow* rw)
{
	rw->draw(_Rectangle);
};

float RectIcon::GetWidth()
{
	return _Rectangle.getLocalBounds().width;
};
float RectIcon::GetHeight()
{
	return _Rectangle.getLocalBounds().height;
};