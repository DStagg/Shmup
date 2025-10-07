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
void BossEnt::Draw(sf::RenderWindow* rw)
{
	GetGraphic().GetSprPntr()->setPosition(sf::Vector2f(GetPresence().GetX(), GetPresence().GetY()));
	rw->draw(*GetGraphic().GetSprPntr());

	if (_TurretA != 0)
		_TurretA->Draw(rw);
	if (_TurretB != 0)
		_TurretB->Draw(rw);
};
