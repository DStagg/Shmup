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
	Random::TimeSeed();

	Service::Init(new SFMLAudio());
	Service::GetAudio().StoreSFX("Shoot", "Shoot.wav");
	Service::GetAudio().StoreSFX("Explosion", "Explosion.wav");
	if (Service::GetAudio().StoreStream("MainBGM", "Paradox.ogg"))
		Service::GetAudio().PlayStream("MainBGM");

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
	_ImgMan.LoadTextureFromFile("DoublePowerup", "DoublePowerup.png");
	_ImgMan.LoadTextureFromFile("LaserPowerup", "LaserPowerup.png");
	_ImgMan.LoadTextureFromFile("HealPowerup", "HealPowerup.png");
	_ImgMan.LoadTextureFromFile("InvinciblePowerup", "InvinciblePowerup.png");
	_ImgMan.LoadTextureFromFile("LaserBeam", "LaserBeam.png");
	_ImgMan.LoadTextureFromFile("Bomb", "Bomb.png");
	
	PopulateAnimations(&_ImgMan);
	_Level.GetFactory().Init(&_Level, &_ImgMan, _Window);

	_Level.GetSize().SetSize((float)_Window->getSize().x, (float)_Window->getSize().y);
	_Level.SetPlayer(_Level.GetFactory().Spawn(EntFactory::Player, _Level.GetSize().GetWidth() / 2.f - 50.f, _Level.GetSize().GetHeight() - 50.f));
	_Level.SetLaser(_Level.GetFactory().Spawn(EntFactory::Laser, 0.f, 0.f));
		
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

	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			SetRunning(false);
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			SetRunning(false);
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num1))
			((PlayerEnt*)_Level.GetPlayer())->_DoubleShot = 5.f;
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num2))
			((PlayerEnt*)_Level.GetPlayer())->_Laser = 2.5f;
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num3))
			((PlayerEnt*)_Level.GetPlayer())->_Invincibility = 5.f;
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num4))
			((PlayerEnt*)_Level.GetPlayer())->_Bombs += 1;
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::P))
		{
			if (Service::GetAudio().StreamPlaying("MainBGM"))
				Service::GetAudio().PauseStream("MainBGM");
			else
				Service::GetAudio().PlayStream("MainBGM");
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
		_Level.GetLaser()->Update(dt);
		_Level.GetLaser()->GetPresence().SetPosition(_Level.GetPlayer()->GetPresence().GetX() + (_Level.GetPlayer()->GetSize().GetWidth() / 2.f), _Level.GetPlayer()->GetPresence().GetY() -_Level.GetSize().GetHeight());
		_Level.GetLaser()->GetSize().SetSize(_Level.GetLaser()->GetGraphic().GetSprPntr()->getLocalBounds().width, _Level.GetSize().GetHeight());
		
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
			if (_Level.GetEnemies().GetEnt(i)->GetStats().GetHP() <= 0)
			{
				_Level.GetEnemies().GetEnt(i)->SetAlive(false);
				_Level.GetSFX().AddEnt(_Level.GetFactory().Spawn(EntFactory::Explosion, _Level.GetEnemies().GetEnt(i)->GetPresence().GetX(), _Level.GetEnemies().GetEnt(i)->GetPresence().GetY()));
				Service::GetAudio().PlaySFX("Explosion");
			}

			if ( _Level.GetEnemies().GetEnt(i)->GetAlive() )
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

		//	Update Powerups
		for (int i = 0; i < _Level.GetPowerups().CountEnts(); i++)
			_Level.GetPowerups().GetEnt(i)->Update(dt);

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

						int ran = Random::Generate(1, 7);
						if (ran == 1)
							_Level.GetPowerups().AddEnt(_Level.GetFactory().Spawn(EntFactory::HealPowerup, _Level.GetEnemies().GetEnt(e)->GetPresence().GetX(), _Level.GetEnemies().GetEnt(e)->GetPresence().GetY()));
						else if (ran == 2)
							_Level.GetPowerups().AddEnt(_Level.GetFactory().Spawn(EntFactory::DoublePowerup, _Level.GetEnemies().GetEnt(e)->GetPresence().GetX(), _Level.GetEnemies().GetEnt(e)->GetPresence().GetY()));
						else if (ran == 3)
							_Level.GetPowerups().AddEnt(_Level.GetFactory().Spawn(EntFactory::LaserPowerup, _Level.GetEnemies().GetEnt(e)->GetPresence().GetX(), _Level.GetEnemies().GetEnt(e)->GetPresence().GetY()));
						else if (ran == 4)
							_Level.GetPowerups().AddEnt(_Level.GetFactory().Spawn(EntFactory::InvinciblePowerup, _Level.GetEnemies().GetEnt(e)->GetPresence().GetX(), _Level.GetEnemies().GetEnt(e)->GetPresence().GetY()));
						else if (ran == 5)
							_Level.GetPowerups().AddEnt(_Level.GetFactory().Spawn(EntFactory::BombPowerup, _Level.GetEnemies().GetEnt(e)->GetPresence().GetX(), _Level.GetEnemies().GetEnt(e)->GetPresence().GetY()));
					}
				}
			}
		
		//	Collision: Laser <-> Enemies
		if (((PlayerEnt*)_Level.GetPlayer())->_Laser > 0.f)
		{
			for (int i = 0; i < _Level.GetEnemies().CountEnts(); i++)
				if (GenBoundBox(_Level.GetLaser()).Intersects(GenBoundBox(_Level.GetEnemies().GetEnt(i))))
				{
					_Level.GetEnemies().GetEnt(i)->SetAlive(false);
					_Level.GetSFX().AddEnt(_Level.GetFactory().Spawn(EntFactory::Explosion, _Level.GetEnemies().GetEnt(i)->GetPresence().GetX(), _Level.GetEnemies().GetEnt(i)->GetPresence().GetY()));
				}
		}

		//	Collision: Player <-> Powerups
		for (int p = 0; p < _Level.GetPowerups().CountEnts(); p++)
			if (GenBoundBox(_Level.GetPowerups().GetEnt(p)).Intersects(GenBoundBox(_Level.GetPlayer())))
			{
				_Level.GetPowerups().GetEnt(p)->SetAlive(false);
				if (_Level.GetPowerups().GetEnt(p)->GetGraphic().GetSprPntr()->getTexture() == _ImgMan.GetTexturePntr("HealPowerup"))
					_Level.GetPlayer()->GetStats().Hurt(-1);
				else if (_Level.GetPowerups().GetEnt(p)->GetGraphic().GetSprPntr()->getTexture() == _ImgMan.GetTexturePntr("DoublePowerup"))
				{
					((PlayerEnt*)_Level.GetPlayer())->_DoubleShot = 5.f;
				}
				else if (_Level.GetPowerups().GetEnt(p)->GetGraphic().GetSprPntr()->getTexture() == _ImgMan.GetTexturePntr("LaserPowerup"))
				{
					((PlayerEnt*)_Level.GetPlayer())->_Laser = 2.5f;
				}
				else if (_Level.GetPowerups().GetEnt(p)->GetGraphic().GetSprPntr()->getTexture() == _ImgMan.GetTexturePntr("InvinciblePowerup"))
				{
					((PlayerEnt*)_Level.GetPlayer())->_Invincibility = 5.f;
				}
				else if (_Level.GetPowerups().GetEnt(p)->GetGraphic().GetSprPntr()->getTexture() == _ImgMan.GetTexturePntr("Bomb"))
				{
					((PlayerEnt*)_Level.GetPlayer())->_Bombs++;
				}
			}

		//	Collision: Player <-> Enemies
		for (int e = 0; e < _Level.GetEnemies().CountEnts(); e++)
			if (GenBoundBox(_Level.GetEnemies().GetEnt(e)).Intersects(GenBoundBox(_Level.GetPlayer())))
			{
				_Level.GetEnemies().GetEnt(e)->SetAlive(false);
				_Level.GetSFX().AddEnt(_Level.GetFactory().Spawn(EntFactory::Explosion, _Level.GetEnemies().GetEnt(e)->GetPresence().GetX(), _Level.GetEnemies().GetEnt(e)->GetPresence().GetY()));
				if (((PlayerEnt*)_Level.GetPlayer())->_Invincibility <= 0.f)
				{
					_Level.GetPlayer()->GetStats().Hurt(1);
					((PlayerEnt*)_Level.GetPlayer())->_Invincibility = 0.5f;
				}
			}

		//	Collision: Player <-> EBullets
		for ( int e = 0; e <_Level.GetEnemyBullets().CountEnts(); e++ )
			if (GenBoundBox(_Level.GetEnemyBullets().GetEnt(e)).Intersects(GenBoundBox(_Level.GetPlayer())))
			{
				_Level.GetEnemyBullets().GetEnt(e)->SetAlive(false);
				if (((PlayerEnt*)_Level.GetPlayer())->_Invincibility <= 0.f)
				{
					_Level.GetPlayer()->GetStats().Hurt(1);
					((PlayerEnt*)_Level.GetPlayer())->_Invincibility = 0.5f;
				}
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
		//	Cull Powerups
		_Level.GetPowerups().Cull(50);
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
	if (((PlayerEnt*)_Level.GetPlayer())->_Laser > 0.f )
		_Level.GetLaser()->Draw(_Window);

	for (int i = 0; i < _Level.GetEnemies().CountEnts(); i++)
		_Level.GetEnemies().GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Level.GetPlayerBullets().CountEnts(); i++)
		_Level.GetPlayerBullets().GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Level.GetEnemyBullets().CountEnts(); i++)
		_Level.GetEnemyBullets().GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Level.GetPowerups().CountEnts(); i++)
		_Level.GetPowerups().GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Level.GetSFX().CountEnts(); i++)
		_Level.GetSFX().GetEnt(i)->Draw(_Window);
	
	//	Draw GUI	//
	//	Health
	for (int i = 0; i < _Level.GetPlayer()->GetStats().GetHP(); i++)
	{
		sf::Sprite pip(*_ImgMan.GetTexturePntr("HealthIcon"));
		pip.setPosition(((i + 1)*5.f) + (i * pip.getTextureRect().width), _Window->getSize().y - (5.f + pip.getTextureRect().height));
		_Window->draw(pip);
	}

	//	Powerups
	int active = 1;
	PlayerEnt* pent = (PlayerEnt*)_Level.GetPlayer();

	if (pent->_Bombs > 0)
	{
		sf::Sprite bombgui(*_ImgMan.GetTexturePntr("Bomb"));
		
		for (int i = 0; i < pent->_Bombs; i++)
		{
			bombgui.setPosition(_Window->getSize().x - ((bombgui.getLocalBounds().width + 10.f) * active), _Window->getSize().y - ((bombgui.getLocalBounds().height + 10.f) * (i + 1)));
			_Window->draw(bombgui);
		}

		active++;
	}
	if (pent->_DoubleShot > 0.f)
	{
		sf::Sprite doublegui(*_ImgMan.GetTexturePntr("DoublePowerup"));
		doublegui.setPosition(_Window->getSize().x - ((doublegui.getLocalBounds().width + 10.f) * (float)active), _Window->getSize().y - (doublegui.getLocalBounds().height + 10.f));
		_Window->draw(doublegui);
		
		sf::RectangleShape doublebar(sf::Vector2f(doublegui.getLocalBounds().width / 2.f, pent->_DoubleShot * 10.f));
		doublebar.setPosition(doublegui.getPosition().x + (doublegui.getLocalBounds().width / 4.f), doublegui.getPosition().y - (10.f + doublebar.getLocalBounds().height));
		doublebar.setFillColor(sf::Color::Green);
		_Window->draw(doublebar);

		active++;
	}
	if (pent->_Laser > 0.f)
	{
		sf::Sprite lasergui(*_ImgMan.GetTexturePntr("LaserPowerup"));
		lasergui.setPosition(_Window->getSize().x - ((lasergui.getLocalBounds().width + 10.f) * (float)active), _Window->getSize().y - (lasergui.getLocalBounds().height + 10.f));
		_Window->draw(lasergui);

		sf::RectangleShape laserbar(sf::Vector2f(lasergui.getLocalBounds().width / 2.f, pent->_Laser * 10.f));
		laserbar.setPosition(lasergui.getPosition().x + (lasergui.getLocalBounds().width / 4.f), lasergui.getPosition().y - (10.f + laserbar.getLocalBounds().height));
		laserbar.setFillColor(sf::Color::Green);
		_Window->draw(laserbar);

		active++;
	}
	if (pent->_Invincibility > 0.f)
	{
		sf::Sprite lasergui(*_ImgMan.GetTexturePntr("InvinciblePowerup"));
		lasergui.setPosition(_Window->getSize().x - ((lasergui.getLocalBounds().width + 10.f) * (float)active), _Window->getSize().y - (lasergui.getLocalBounds().height + 10.f));
		_Window->draw(lasergui);

		sf::RectangleShape laserbar(sf::Vector2f(lasergui.getLocalBounds().width / 2.f, pent->_Invincibility * 10.f));
		laserbar.setPosition(lasergui.getPosition().x + (lasergui.getLocalBounds().width / 4.f), lasergui.getPosition().y - (10.f + laserbar.getLocalBounds().height));
		laserbar.setFillColor(sf::Color::Green);
		_Window->draw(laserbar);

		active++;
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
	for (int i = 0; i < _Level.GetPowerups().CountEnts(); i++)
		DebugDrawEntity(_Level.GetPowerups().GetEnt(i), _Window, sf::Color::White);
	DebugDrawEntity(_Level.GetLaser(), _Window, sf::Color::Green);
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