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
	_ImgMan.LoadTextureFromFile("BombEnemy", "BombEnemy.png");
	_ImgMan.LoadTextureFromFile("DroneEnemy", "DroneEnemy.png");
	_ImgMan.LoadTextureFromFile("SpreaderEnemy", "SpreaderEnemy.png");
	_ImgMan.LoadTextureFromFile("SwarmEnemy", "SwarmEnemy.png");
	_ImgMan.LoadTextureFromFile("TankEnemy", "TankEnemy.png");
	_ImgMan.LoadTextureFromFile("HealthIcon", "HealthIcon.png");
	_ImgMan.LoadTextureFromFile("EBullet", "EnemyBullet.png");
	_ImgMan.LoadTextureFromFile("Explosion", "Explosion.png");
	
	PopulateAnimations(&_ImgMan);
	_Level.GetFactory().Init(&_Level, &_ImgMan, _Window);

	_Level.GetSize().SetSize((float)_Window->getSize().x, (float)_Window->getSize().y);
	_Level.SetPlayer(_Level.GetFactory().Spawn(EntFactory::Player, _Level.GetSize().GetWidth() / 2.f - 50.f, _Level.GetSize().GetHeight() - 50.f));
		
	_SpawnQueue.Load("Queue.bin");
	//GenSpawnQueue(&_SpawnQueue);
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
			_Level.GetEnemies().AddEnt(_Level.GetFactory().Spawn(EntFactory::BombEnemy, 100.f, 100.f));
			_Level.GetEnemies().AddEnt(_Level.GetFactory().Spawn(EntFactory::DroneEnemy, 200.f, 100.f));
			_Level.GetEnemies().AddEnt(_Level.GetFactory().Spawn(EntFactory::SwarmEnemy, 300.f, 100.f));
			_Level.GetEnemies().AddEnt(_Level.GetFactory().Spawn(EntFactory::SpreaderEnemy, 400.f, 100.f));
			_Level.GetEnemies().AddEnt(_Level.GetFactory().Spawn(EntFactory::TankEnemy, 500.f, 100.f));
		}
	}

	if (_Level.GetPlayer()->GetAlive())
	{
		//	Progress Spawn Queue
		if (_SpawnQueue.CountEntries() > 0)
		{
			_SpawnQueue.AddTime(dt);
			while (_SpawnQueue.GetTime() >= _SpawnQueue.PeekFront()._Delay)
			{
				SpawnEntry entry = _SpawnQueue.PopFront();
				_Level.GetEnemies().AddEnt(_Level.GetFactory().Spawn(entry._ID, entry._X, entry._Y));

				if (_SpawnQueue.CountEntries() == 0)
					break;
			}
		}

		_Level.GetPlayer()->Update(dt);

		//	Spawn Bullets
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (_ShootTimer >= _ShootDelay))
		{
			_ShootTimer = 0.f;
			_Level.GetPlayerBullets().AddEnt(_Level.GetFactory().Spawn(EntFactory::PlayerBullet, _Level.GetPlayer()->GetPresence().GetX() + (_Level.GetPlayer()->GetSize().GetWidth() / 2.f), _Level.GetPlayer()->GetPresence().GetY()));
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

		//	Update SFX
		for (int i = 0; i < _Level.GetSFX().CountEnts(); i++)
			_Level.GetSFX().GetEnt(i)->Update(dt);

		//	Collision: PBullets <-> Enemies
		for (int b = 0; b < _Level.GetPlayerBullets().CountEnts(); b++)
			for (int e = 0; e < _Level.GetEnemies().CountEnts(); e++)
			{
				if (GenBoundBox(_Level.GetPlayerBullets().GetEnt(b)).Intersects(GenBoundBox(_Level.GetEnemies().GetEnt(e))))
				{
					_Level.GetPlayerBullets().GetEnt(b)->SetAlive(false);
					_Level.GetEnemies().GetEnt(e)->GetStats().Hurt(1);
					if (_Level.GetEnemies().GetEnt(e)->GetStats().GetHP() <= 0)
					{
						_Level.GetEnemies().GetEnt(e)->SetAlive(false);
						_Level.GetSFX().AddEnt(_Level.GetFactory().Spawn(EntFactory::Explosion, _Level.GetEnemies().GetEnt(e)->GetPresence().GetX(), _Level.GetEnemies().GetEnt(e)->GetPresence().GetY()));
					}
				}
			}

		//	Collision: Player <-> Enemies
		for (int e = 0; e < _Level.GetEnemies().CountEnts(); e++)
			if (GenBoundBox(_Level.GetEnemies().GetEnt(e)).Intersects(GenBoundBox(_Level.GetPlayer())))
			{
				_Level.GetEnemies().GetEnt(e)->SetAlive(false);
				_Level.GetSFX().AddEnt(_Level.GetFactory().Spawn(EntFactory::Explosion, _Level.GetEnemies().GetEnt(e)->GetPresence().GetX(), _Level.GetEnemies().GetEnt(e)->GetPresence().GetY()));
				_Level.GetPlayer()->GetStats().Hurt(1);
			}

		//	Collision: Player <-> EBullets
		for ( int e = 0; e <_Level.GetEnemyBullets().CountEnts(); e++ )
			if (GenBoundBox(_Level.GetEnemyBullets().GetEnt(e)).Intersects(GenBoundBox(_Level.GetPlayer())))
			{
				_Level.GetEnemyBullets().GetEnt(e)->SetAlive(false);
				_Level.GetPlayer()->GetStats().Hurt(1);
			}

		//	Check Player Health
		if (_Level.GetPlayer()->GetStats().GetHP() <= 0)
			_Level.GetPlayer()->SetAlive(false);

		//	Cull Bullets
		_Level.GetPlayerBullets().Cull(100);
		//	Cull Enemy Bullets
		_Level.GetEnemyBullets().Cull(100);
		//	Cull Enemies
		_Level.GetEnemies().Cull(50);
		//	Cull SFX
		_Level.GetSFX().Cull(50);
	}
	else
		GetManager()->PushScene(new LoseScene(_Window));
	
};
void ShootScene::DrawScreen()
{
	//	Draw Ents	//

	_Level.GetPlayer()->Draw(_Window);

	for (int i = 0; i < _Level.GetEnemies().CountEnts(); i++)
		_Level.GetEnemies().GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Level.GetPlayerBullets().CountEnts(); i++)
		_Level.GetPlayerBullets().GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Level.GetEnemyBullets().CountEnts(); i++)
		_Level.GetEnemyBullets().GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Level.GetSFX().CountEnts(); i++)
		_Level.GetSFX().GetEnt(i)->Draw(_Window);
	
	//	Draw GUI	//

	for (int i = 0; i < _Level.GetPlayer()->GetStats().GetHP(); i++)
	{
		sf::Sprite pip(*_ImgMan.GetTexturePntr("HealthIcon"));
		pip.setPosition(((i + 1)*5.f) + (i * pip.getTextureRect().width), _Window->getSize().y - (5.f + pip.getTextureRect().height));
		_Window->draw(pip);
	}

	/*
	DebugDrawEntity(_Level.GetPlayer(), _Window, sf::Color::Blue);
	for (int i = 0; i < _Level.GetPlayerBullets().CountEnts(); i++)
		DebugDrawEntity(_Level.GetPlayerBullets().GetEnt(i), _Window, sf::Color::Cyan);
	for (int i = 0; i < _Level.GetEnemies().CountEnts(); i++)
		DebugDrawEntity(_Level.GetEnemies().GetEnt(i), _Window, sf::Color::Red);
	for (int i = 0; i < _Level.GetEnemyBullets().CountEnts(); i++)
		DebugDrawEntity(_Level.GetEnemyBullets().GetEnt(i), _Window, sf::Color::Magenta);
	for (int i = 0; i < _Level.GetSFX().CountEnts(); i++)
		DebugDrawEntity(_Level.GetSFX().GetEnt(i), _Window, sf::Color::Yellow);
		*/
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