#include "BossEnt.h"

BossEnt::BossEnt(Level* lvl) : Entity(lvl)
{
	_TurretA = 0;
	_TurretB = 0;
};
BossEnt::~BossEnt()
{

};

void BossEnt::InitTurrets(BasicEnt* ta, BasicEnt* tb)
{
	_TurretA = ta;
	_TurretB = tb;

	ta->GetPresence().SetPosition(GetPresence().GetX() + 32, (GetPresence().GetY() + 256) - 96);
	tb->GetPresence().SetPosition((GetPresence().GetX() + 256) - 96, (GetPresence().GetY() + 256) - 96);
}

void BossEnt::Update(float dt)
{
	GetPresence().UpdatePosition(dt);

	if (_TurretA != 0)
		_TurretA->Update(dt);
	if (_TurretB != 0)
		_TurretB->Update(dt);

	GetGraphic().Play(dt);
	GetSize().SetSize((float)GetGraphic().GetCurrentFrame()._Width, (float)GetGraphic().GetCurrentFrame()._Height);
}
void BossEnt::Draw(SDL_Renderer* renderer)
{
	SDL_FRect dstrect;
	dstrect.x = GetPresence().GetX();
	dstrect.y = GetPresence().GetY();
	dstrect.w = GetGraphic().GetSprPntr()->_SrcRect.w;
	dstrect.h = GetGraphic().GetSprPntr()->_SrcRect.h;

	SDL_RenderTexture(renderer, GetGraphic().GetSprPntr()->_Texture, &GetGraphic().GetSprPntr()->_SrcRect, &dstrect);
	
	if (_TurretA != 0)
		_TurretA->Draw(renderer);
	if (_TurretB != 0)
		_TurretB->Draw(renderer);
};
