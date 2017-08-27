#include "ShootScene.h"

ShootScene::ShootScene(sf::RenderWindow* win)
{
	_Window = win;
};
ShootScene::~ShootScene()
{

};

void ShootScene::Begin()
{
	_Player.SetSize(32.f, 64.f);
	_Player.SetPosition((_Window->getSize().x - _Player.GetWidth()) / 2.f, _Window->getSize().y - _Player.GetHeight());
};
void ShootScene::End()
{
	_Bullets.Cull(0);
	_Enemies.Cull(0);
};
void ShootScene::Pause()
{

};
void ShootScene::Resume()
{

};
void ShootScene::Update(float dt)
{
	_ShootTimer += dt;
	_SpawnTimer += dt;

	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			SetRunning(false);
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			SetRunning(false);
	}

	//	Spawn Enemies
	if (_SpawnTimer >= _SpawnDelay)
	{
		_SpawnTimer = 0.f;
		Entity* ent = new Entity();
		ent->SetSize(50.f, 50.f);
		ent->SetVelocity(0.f, 100.f);
		ent->SetPosition((float)Random::Generate(0,(int)(_Window->getSize().x - 50.f)), -50.f);
		_Enemies.AddEnt(ent);
	}


	//	Control Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_Player.SetYVel(-200.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		_Player.SetYVel(200.f);
	else
		_Player.SetYVel(0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_Player.SetXVel(-200.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_Player.SetXVel(200.f);
	else
		_Player.SetXVel(0.f);

	_Player.SetX(_Player.GetX() + (_Player.GetXVel() * dt));
	_Player.SetY(_Player.GetY() + (_Player.GetYVel() * dt));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (_ShootTimer >= _ShootDelay))
	{
		_ShootTimer = 0.f;
		Entity* bullet = new Entity();
		bullet->SetPosition(_Player.GetX(), _Player.GetY());
		bullet->SetSize(16.f, 16.f);
		bullet->SetYVel(_Player.GetYVel() - 100.f);
		if (bullet->GetYVel() > -100.f)
			bullet->SetYVel(-100.f);
		_Bullets.AddEnt(bullet);
	}

	//	Update Bullets
	for (int i = 0; i < _Bullets.CountEnts(); i++)
	{
		Entity* ent = _Bullets.GetEnt(i);
		ent->SetX(ent->GetX() + (ent->GetXVel() * dt));
		ent->SetY(ent->GetY() + (ent->GetYVel() * dt));

		if (ent->GetY() <= -ent->GetHeight())
			_Bullets.DelEnt(ent);
	}

	//	Update Enemies
	for (int i = 0; i < _Enemies.CountEnts(); i++)
	{
		Entity* ent = _Enemies.GetEnt(i);
		ent->SetX(ent->GetX() + (ent->GetXVel() * dt));
		ent->SetY(ent->GetY() + (ent->GetYVel() * dt));

		if (ent->GetY() > _Window->getSize().y)
			_Enemies.DelEnt(ent);
	}

	//	Collision: Bullets <-> Enemies
	for (int b = 0; b < _Bullets.CountEnts(); b++ )
		for (int e = 0; e < _Enemies.CountEnts(); e++)
		{
			if (GenBoundBox(_Bullets.GetEnt(b)).Intersects(GenBoundBox(_Enemies.GetEnt(e))))
			{
				_Bullets.GetEnt(b)->SetAlive(false);
				_Enemies.GetEnt(e)->SetAlive(false);
			}
		}

	//	Cull Bullets
	_Bullets.Cull(100);
	//	Cull Enemies
	_Enemies.Cull(50);
};
void ShootScene::DrawScreen()
{
	DebugDrawEntity(&_Player, _Window, sf::Color::Blue);

	for (int i = 0; i < _Bullets.CountEnts(); i++)
		DebugDrawEntity(_Bullets.GetEnt(i), _Window, sf::Color::Cyan);

	for (int i = 0; i < _Enemies.CountEnts(); i++)
		DebugDrawEntity(_Enemies.GetEnt(i), _Window, sf::Color::Red);
};

///

void DebugDrawEntity(Entity* ent, sf::RenderWindow* win, sf::Color col)
{
	sf::RectangleShape rect;
	rect.setPosition(ent->GetX(), ent->GetY());
	rect.setSize(sf::Vector2f(ent->GetWidth(), ent->GetHeight()));
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(col);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	win->draw(rect);
};