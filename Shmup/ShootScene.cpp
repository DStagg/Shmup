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
	_ImgMan.LoadTextureFromFile("Player", "Player.png");
	_ImgMan.LoadTextureFromFile("PBullet", "PlayerBullet.png");
	_ImgMan.LoadTextureFromFile("Enemy", "Enemy.png");
	_ImgMan.LoadTextureFromFile("BombEnemy", "BombEnemy.png");
	
	PopulateAnimations(&_ImgMan);

	_Factory.Init(&_ImgMan, _Window);

	_Player = _Factory.Spawn(EntFactory::Player, _Window->getSize().x / 2.f - 50.f, _Window->getSize().y - 50.f);
	
};
void ShootScene::End()
{
	delete _Player;
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

	//	Check if we need to quit
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			SetRunning(false);
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			SetRunning(false);
	}

	if (_Player->GetAlive())
	{
		//	Spawn Enemies
		if (_SpawnTimer >= _SpawnDelay)
		{
			_SpawnTimer = 0.f;
			_Enemies.AddEnt(_Factory.Spawn(EntFactory::BombEnemy, (float)Random::Generate(0, (int)(_Window->getSize().x - 50.f)), 0.f - 50.f));
		}

		_Player->Update(dt);

		//	Spawn Bullets
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (_ShootTimer >= _ShootDelay))
		{
			_ShootTimer = 0.f;
			_Bullets.AddEnt(_Factory.Spawn(EntFactory::PlayerBullet, _Player->GetPresence().GetX() + (_Player->GetSize().GetWidth() / 2.f), _Player->GetPresence().GetY()));
		}

		//	Update Bullets
		for (int i = 0; i < _Bullets.CountEnts(); i++)
		{
			_Bullets.GetEnt(i)->Update(dt);

			if (_Bullets.GetEnt(i)->GetPresence().GetY() <= -_Bullets.GetEnt(i)->GetSize().GetHeight())
				_Bullets.DelEnt(_Bullets.GetEnt(i));
		}

		//	Update Enemies
		for (int i = 0; i < _Enemies.CountEnts(); i++)
		{
			_Enemies.GetEnt(i)->Update(dt);
			
			if (_Enemies.GetEnt(i)->GetPresence().GetY() > _Window->getSize().y)
				_Enemies.DelEnt(_Enemies.GetEnt(i));
		}

		//	Collision: Bullets <-> Enemies
		for (int b = 0; b < _Bullets.CountEnts(); b++)
			for (int e = 0; e < _Enemies.CountEnts(); e++)
			{
				if (GenBoundBox(_Bullets.GetEnt(b)).Intersects(GenBoundBox(_Enemies.GetEnt(e))))
				{
					_Bullets.GetEnt(b)->SetAlive(false);
					_Enemies.GetEnt(e)->SetAlive(false);
				}
			}

		//	Collisin: Player <-> Enemies
		for (int e = 0; e < _Enemies.CountEnts(); e++)
			if (GenBoundBox(_Enemies.GetEnt(e)).Intersects(GenBoundBox(_Player)))
			{
				_Enemies.GetEnt(e)->SetAlive(false);
				_Player->SetAlive(false);
			}

		//	Cull Bullets
		_Bullets.Cull(100);
		//	Cull Enemies
		_Enemies.Cull(50);
	}
	else
		GetManager()->PushScene(new LoseScene(_Window));
	
};
void ShootScene::DrawScreen()
{
	_Player->Draw(_Window);

	for (int i = 0; i < _Bullets.CountEnts(); i++)
		_Bullets.GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Enemies.CountEnts(); i++)
		_Enemies.GetEnt(i)->Draw(_Window);


	DebugDrawEntity(_Player, _Window, sf::Color::Blue);
	for (int i = 0; i < _Bullets.CountEnts(); i++)
		DebugDrawEntity(_Bullets.GetEnt(i), _Window, sf::Color::Cyan);
	for (int i = 0; i < _Enemies.CountEnts(); i++)
		DebugDrawEntity(_Enemies.GetEnt(i), _Window, sf::Color::Red);
};

///

void DebugDrawEntity(Entity* ent, sf::RenderWindow* win, sf::Color col)
{
	sf::RectangleShape rect;
	rect.setPosition(ent->GetPresence().GetX(), ent->GetPresence().GetY());
	rect.setSize(sf::Vector2f(ent->GetSize().GetWidth(), ent->GetSize().GetHeight()));
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(col);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	win->draw(rect);
};