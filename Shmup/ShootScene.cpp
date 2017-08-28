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
	_ImgMan.LoadTextureFromFile("DroneEnemy", "DroneEnemy.png");
	_ImgMan.LoadTextureFromFile("SpreaderEnemy", "SpreaderEnemy.png");
	_ImgMan.LoadTextureFromFile("SwarmEnemy", "SwarmEnemy.png");
	_ImgMan.LoadTextureFromFile("TankEnemy", "TankEnemy.png");
	_ImgMan.LoadTextureFromFile("HealthIcon", "HealthIcon.png");
	
	PopulateAnimations(&_ImgMan);
	_Factory.Init(&_Level, &_ImgMan, _Window);

	_Level.GetSize().SetSize((float)_Window->getSize().x, (float)_Window->getSize().y);
	_Level.SetPlayer(_Factory.Spawn(EntFactory::Player, _Level.GetSize().GetWidth() / 2.f - 50.f, _Level.GetSize().GetHeight() - 50.f));
		
};
void ShootScene::End()
{

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
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
		{
			_Level.GetEnemies().AddEnt(_Factory.Spawn(EntFactory::BombEnemy, 100.f, 100.f));
			_Level.GetEnemies().AddEnt(_Factory.Spawn(EntFactory::DroneEnemy, 200.f, 100.f));
			_Level.GetEnemies().AddEnt(_Factory.Spawn(EntFactory::SwarmEnemy, 300.f, 100.f));
			_Level.GetEnemies().AddEnt(_Factory.Spawn(EntFactory::SpreaderEnemy, 400.f, 100.f));
			_Level.GetEnemies().AddEnt(_Factory.Spawn(EntFactory::TankEnemy, 500.f, 100.f));
		}
	}

	if (_Level.GetPlayer()->GetAlive())
	{
		//	Spawn Enemies
		if (_SpawnTimer >= _SpawnDelay)
		{
			_SpawnTimer = 0.f;
			_Level.GetEnemies().AddEnt(_Factory.Spawn(EntFactory::BombEnemy, (float)Random::Generate(0, (int)(_Level.GetSize().GetWidth() - 50.f)), 0.f - 50.f));
		}

		_Level.GetPlayer()->Update(dt);

		//	Spawn Bullets
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (_ShootTimer >= _ShootDelay))
		{
			_ShootTimer = 0.f;
			_Level.GetPlayerBullets().AddEnt(_Factory.Spawn(EntFactory::PlayerBullet, _Level.GetPlayer()->GetPresence().GetX() + (_Level.GetPlayer()->GetSize().GetWidth() / 2.f), _Level.GetPlayer()->GetPresence().GetY()));
		}

		//	Update Bullets
		for (int i = 0; i < _Level.GetPlayerBullets().CountEnts(); i++)
		{
			_Level.GetPlayerBullets().GetEnt(i)->Update(dt);

			if (_Level.GetPlayerBullets().GetEnt(i)->GetPresence().GetY() <= -_Level.GetPlayerBullets().GetEnt(i)->GetSize().GetHeight())
				_Level.GetPlayerBullets().DelEnt(_Level.GetPlayerBullets().GetEnt(i));
		}

		//	Update Enemies
		for (int i = 0; i < _Level.GetEnemies().CountEnts(); i++)
		{
			_Level.GetEnemies().GetEnt(i)->Update(dt);
			
			if (_Level.GetEnemies().GetEnt(i)->GetPresence().GetY() > _Level.GetSize().GetHeight())
				_Level.GetEnemies().DelEnt(_Level.GetEnemies().GetEnt(i));
		}

		//	Update Enemy Bullets
		for (int i = 0; i < _Level.GetEnemyBullets().CountEnts(); i++)
		{
			_Level.GetEnemyBullets().GetEnt(i)->Update(dt);

			if (_Level.GetEnemyBullets().GetEnt(i)->GetPresence().GetY() > _Level.GetSize().GetHeight())
				_Level.GetEnemyBullets().DelEnt(_Level.GetEnemyBullets().GetEnt(i));
		}

		//	Collision: Bullets <-> Enemies
		for (int b = 0; b < _Level.GetPlayerBullets().CountEnts(); b++)
			for (int e = 0; e < _Level.GetEnemies().CountEnts(); e++)
			{
				if (GenBoundBox(_Level.GetPlayerBullets().GetEnt(b)).Intersects(GenBoundBox(_Level.GetEnemies().GetEnt(e))))
				{
					_Level.GetPlayerBullets().GetEnt(b)->SetAlive(false);
					_Level.GetEnemies().GetEnt(e)->GetStats().Hurt(1);
					if (_Level.GetEnemies().GetEnt(e)->GetStats().GetHP() <= 0 )
						_Level.GetEnemies().GetEnt(e)->SetAlive(false);
				}
			}

		//	Collisin: Player <-> Enemies
		for (int e = 0; e < _Level.GetEnemies().CountEnts(); e++)
			if (GenBoundBox(_Level.GetEnemies().GetEnt(e)).Intersects(GenBoundBox(_Level.GetPlayer())))
			{
				_Level.GetEnemies().GetEnt(e)->SetAlive(false);
				_Level.GetPlayer()->GetStats().Hurt(1);
				if ( _Level.GetPlayer()->GetStats().GetHP() <= 0 )
					_Level.GetPlayer()->SetAlive(false);
			}

		//	Cull Bullets
		_Level.GetPlayerBullets().Cull(100);
		//	Cull Enemies
		_Level.GetEnemies().Cull(50);
	}
	else
		GetManager()->PushScene(new LoseScene(_Window));
	
};
void ShootScene::DrawScreen()
{
	//	Draw Ents	//

	_Level.GetPlayer()->Draw(_Window);

	for (int i = 0; i < _Level.GetPlayerBullets().CountEnts(); i++)
		_Level.GetPlayerBullets().GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Level.GetEnemies().CountEnts(); i++)
		_Level.GetEnemies().GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Level.GetEnemyBullets().CountEnts(); i++)
		_Level.GetEnemyBullets().GetEnt(i)->Draw(_Window);

	
	//	Draw GUI	//

	for (int i = 0; i < _Level.GetPlayer()->GetStats().GetHP(); i++)
	{
		sf::Sprite pip(*_ImgMan.GetTexturePntr("HealthIcon"));
		pip.setPosition(((i + 1)*5.f) + (i * pip.getTextureRect().width), _Window->getSize().y - (5.f + pip.getTextureRect().height));
		_Window->draw(pip);
	}

	DebugDrawEntity(_Level.GetPlayer(), _Window, sf::Color::Blue);
	for (int i = 0; i < _Level.GetPlayerBullets().CountEnts(); i++)
		DebugDrawEntity(_Level.GetPlayerBullets().GetEnt(i), _Window, sf::Color::Cyan);
	for (int i = 0; i < _Level.GetEnemies().CountEnts(); i++)
		DebugDrawEntity(_Level.GetEnemies().GetEnt(i), _Window, sf::Color::Red);
	for (int i = 0; i < _Level.GetEnemyBullets().CountEnts(); i++)
		DebugDrawEntity(_Level.GetEnemyBullets().GetEnt(i), _Window, sf::Color::Magenta);
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