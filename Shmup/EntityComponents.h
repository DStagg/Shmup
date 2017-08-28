#ifndef ENTITYCOMPONENTS_H
#define ENTITYCOMPONENTS_H

class Size
{
public:

	Size(float w = 1.f, float h = 1.f);
	
	void SetWidth(float w);
	void SetHeight(float h);
	void SetSize(float w, float h);

	float GetWidth();
	float GetHeight();

private:

	float _Width;
	float _Height;
};

class Presence
{
public:

	Presence(float x = 0.f, float y = 0.f, float xv = 0.f, float yv = 0.f);

	void SetX(float x);
	void SetY(float y);
	void SetPosition(float x, float y);

	void SetXVel(float xv);
	void SetYVel(float yv);
	void SetVelocity(float xv, float yv);

	float GetX();
	float GetY();

	float GetXVel();
	float GetYVel();

	void UpdatePosition(float dt);

private:
	
	float _X, _Y;
	float _XVel, _YVel;
};

class Stats
{
public:

	Stats(int hp = 1);

	void SetHP(int hp);
	int GetHP();
	void SetMaxHP(int hp);
	int GetMaxHP();

	void Hurt(int hp);

private:

	int _CurrentHP;
	int _MaximumHP;
};

#endif