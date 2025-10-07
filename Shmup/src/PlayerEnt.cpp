#include "PlayerEnt.h"
#include "Level.h"

PlayerEnt::PlayerEnt(Level* lvl , SDL_Renderer* renderer) : Entity(lvl)
{
	_Window = renderer;
};

void PlayerEnt::Update(float dt)
{
	_ShootTimer += dt;

	if (_DoubleShot > 0.f)
		_DoubleShot -= dt;
	if (_Invincibility > 0.f)
		_Invincibility -= dt;
	if (_Laser > 0.f)
		_Laser -= dt;


	//	Control Player
	if (_W && !_S)
		GetPresence().SetYVel(-200.f);
	else if (_S && !_W)
		GetPresence().SetYVel(200.f);
	else
		GetPresence().SetYVel(0.f);

	if (_A && !_D)
		GetPresence().SetXVel(-200.f);
	else if (_D && !_A)
		GetPresence().SetXVel(200.f);
	else
		GetPresence().SetXVel(0.f);

	if (GetStats().GetHP() <= 0)
		SetAlive(false);

	if ((GetStats().GetHP() == 1) && (GetGraphic().GetCurrentAnimName() != "Death"))
		GetGraphic().Swap("Death");
	else if ((GetStats().GetHP() > 1) && (GetGraphic().GetCurrentAnimName() == "Death"))
		GetGraphic().Swap("Idle");

	GetPresence().UpdatePosition(dt);

	if (GetPresence().GetX() < 0.f)
		GetPresence().SetX(0.f);
	else if (GetPresence().GetX() > GetLevel()->GetSize().GetWidth() - GetSize().GetWidth())
		GetPresence().SetX(GetLevel()->GetSize().GetWidth() - GetSize().GetWidth());

	if (GetPresence().GetY() < 0.f)
		GetPresence().SetY(0.f);
	if (GetPresence().GetY() > GetLevel()->GetSize().GetHeight() - GetSize().GetHeight())
		GetPresence().SetY(GetLevel()->GetSize().GetHeight() - GetSize().GetHeight());

	if (_Space && (_ShootTimer >= _ShootDelay))
	{
		_ShootTimer = 0.f;

		Service::GetAudio().PlaySFX("Shoot");

		if (_DoubleShot > 0.f)
		{
			GetLevel()->GetPlayerBullets().AddEnt(GetLevel()->GetFactory().Spawn(EntFactory::PlayerBullet, GetPresence().GetX() , GetPresence().GetY()));
			GetLevel()->GetPlayerBullets().AddEnt(GetLevel()->GetFactory().Spawn(EntFactory::PlayerBullet, GetPresence().GetX() + GetSize().GetWidth(), GetPresence().GetY()));
		}
		else
			GetLevel()->GetPlayerBullets().AddEnt(GetLevel()->GetFactory().Spawn(EntFactory::PlayerBullet, GetPresence().GetX() + (GetSize().GetWidth() / 2.f), GetPresence().GetY()));
	
	}

	if (_B && (_ShootTimer >= _ShootDelay) && (_Bombs >= 1))
	{
		_ShootTimer = 0.f;
		_Bombs--;

		for (int i = 0; i < GetLevel()->GetEnemies().CountEnts(); i++)
			GetLevel()->GetEnemies().GetEnt(i)->GetStats().SetHP(0);
		for (int i = 0; i < GetLevel()->GetEnemyBullets().CountEnts(); i++)
			GetLevel()->GetEnemyBullets().GetEnt(i)->SetAlive(false);
	}


	GetGraphic().Play(dt);
	GetSize().SetSize((float)GetGraphic().GetCurrentFrame()._Width, (float)GetGraphic().GetCurrentFrame()._Height);

};

void PlayerEnt::Draw(SDL_Renderer* renderer)
{
	SDL_FRect dstrect;
	dstrect.x = GetPresence().GetX();
	dstrect.y = GetPresence().GetY();
	dstrect.w = GetGraphic().GetSprPntr()->_SrcRect.w;
	dstrect.h = GetGraphic().GetSprPntr()->_SrcRect.h;

	SDL_RenderTexture(renderer, GetGraphic().GetSprPntr()->_Texture, &GetGraphic().GetSprPntr()->_SrcRect, &dstrect);
};