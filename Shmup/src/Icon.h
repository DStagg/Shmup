#ifndef ICON_H
#define ICON_H

#include <SFML\Graphics.hpp>
#include "ImageManager.h"

class Entity;

class Icon
{
public:

	Icon(Entity* ent);

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow* rw) = 0;

	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;

protected:

	Entity* _Entity;
};

class SpriteIcon : public Icon
{
public:

	SpriteIcon(Entity* ent, sf::Sprite spr);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	float GetWidth();
	float GetHeight();

private:

	sf::Sprite _Sprite;
};

class AnimIcon : public Icon
{
public:

	AnimIcon(Entity* ent, sf::Sprite spr, Animation anim);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	float GetWidth();
	float GetHeight();

private:

	sf::Sprite _Sprite;
	Animation _Animation;

};

class RectIcon : public Icon
{
public:

	RectIcon(Entity* ent, sf::Color col);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	float GetWidth();
	float GetHeight();

private:

	sf::RectangleShape _Rectangle;

};

#endif