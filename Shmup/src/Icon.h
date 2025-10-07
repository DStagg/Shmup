#pragma once

#include <SDL3/SDL.h>
#include "ImageManager.h"
#include "EntityComponents.h"

class Entity;

class Icon
{
public:

	Icon(Entity* ent);

	virtual void Update(float dt) = 0;
	virtual void Draw(SDL_Renderer* renderer) = 0;

	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;

protected:

	Entity* _Entity;
};

class SpriteIcon : public Icon
{
public:

	SpriteIcon(Entity* ent, Sprite spr);

	void Update(float dt);
	void Draw(SDL_Renderer* renderer);

	float GetWidth();
	float GetHeight();

private:

	Sprite _Sprite;
};

class AnimIcon : public Icon
{
public:

	AnimIcon(Entity* ent, Sprite spr, Animation anim);

	void Update(float dt);
	void Draw(SDL_Renderer* renderer);

	float GetWidth();
	float GetHeight();

private:

	Sprite _Sprite;
	Animation _Animation;

};

class RectIcon : public Icon
{
public:

	RectIcon(Entity* ent, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	void Update(float dt);
	void Draw(SDL_Renderer* renderer);

	float GetWidth();
	float GetHeight();

private:

	SDL_FRect _Rectangle;
	Uint8 _R;
	Uint8 _G;
	Uint8 _B;
	Uint8 _A;
};