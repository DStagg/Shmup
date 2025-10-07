#include "Icon.h"
#include "Entity.h"

Icon::Icon(Entity* ent)
{
	_Entity = ent;
};

/////

SpriteIcon::SpriteIcon(Entity* ent, Sprite spr) : Icon(ent)
{
	_Sprite = spr;
};

void SpriteIcon::Update(float dt)
{

};

void SpriteIcon::Draw(SDL_Renderer* renderer)
{
	SDL_FRect dstrect;
	dstrect.x = _Entity->GetPresence().GetX();
	dstrect.y = _Entity->GetPresence().GetY();
	dstrect.w = _Sprite._SrcRect.w;
	dstrect.h = _Sprite._SrcRect.h;

	SDL_RenderTexture(renderer, _Sprite._Texture, &_Sprite._SrcRect, &dstrect);

};

float SpriteIcon::GetWidth()
{
	return _Sprite._SrcRect.w;
};
float SpriteIcon::GetHeight()
{
	return _Sprite._SrcRect.h;
};

/////

AnimIcon::AnimIcon(Entity* ent, Sprite spr, Animation anim) : Icon(ent)
{
	_Sprite = spr;
	_Animation = anim;
};

void AnimIcon::Update(float dt)
{
	_Animation.Play(dt);
	_Sprite._SrcRect = AnimIntoRect(_Animation);
};

void AnimIcon::Draw(SDL_Renderer* renderer)
{
	SDL_FRect dstrect;
	dstrect.x = _Entity->GetPresence().GetX();
	dstrect.y = _Entity->GetPresence().GetY();
	dstrect.w = _Sprite._SrcRect.w;
	dstrect.h = _Sprite._SrcRect.h;

	SDL_RenderTexture(renderer, _Sprite._Texture, &_Sprite._SrcRect, &dstrect);
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

RectIcon::RectIcon(Entity* ent, Uint8 r, Uint8 g, Uint8 b, Uint8 a) : Icon(ent)
{
	_R = r;
	_G = g;
	_B = b;
	_A = a;
};

void RectIcon::Update(float dt)
{
	_Rectangle.x = _Entity->GetPresence().GetX();
	_Rectangle.y = _Entity->GetPresence().GetY();
	_Rectangle.w = _Entity->GetSize().GetWidth();
	_Rectangle.h = _Entity->GetSize().GetHeight();
};

void RectIcon::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, _R, _G, _B, _A);
	SDL_RenderRect(renderer, &_Rectangle);
};

float RectIcon::GetWidth()
{
	return _Rectangle.w;
};
float RectIcon::GetHeight()
{
	return _Rectangle.h;
};