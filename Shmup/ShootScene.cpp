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

	_Player.GetSize().SetSize(64.f, 32.f);
	_Player.GetPresence().SetPosition((_Window->getSize().x - _Player.GetSize().GetWidth()) / 2.f, _Window->getSize().y - _Player.GetSize().GetHeight());

	_Player.SetIcon(new AnimIcon(&_Player, sf::Sprite(*_ImgMan.GetTexturePntr("Player")), _ImgMan.GetAnimation("Player_Idle")));
	
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

	//	Check if we need to quit
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			SetRunning(false);
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			SetRunning(false);
	}

	if (_Player.GetAlive())
	{
		//	Spawn Enemies
		if (_SpawnTimer >= _SpawnDelay)
		{
			_SpawnTimer = 0.f;

			Entity* ent = new Entity();
			ent->SetIcon(new AnimIcon(ent, sf::Sprite(*_ImgMan.GetTexturePntr("BombEnemy")), _ImgMan.GetAnimation("BombEnemy_Idle")));
			ent->GetPresence().SetVelocity(0.f, 100.f);
			ent->GetSize().SetSize(50.f, 50.f);
			ent->GetPresence().SetPosition((float)Random::Generate(0, (int)(_Window->getSize().x - 50.f)), 0.f - 50.f);
			_Enemies.AddEnt(ent);

		}

		//	Control Player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_Player.GetPresence().SetYVel(-200.f);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			_Player.GetPresence().SetYVel(200.f);
		else
			_Player.GetPresence().SetYVel(0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_Player.GetPresence().SetXVel(-200.f);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			_Player.GetPresence().SetXVel(200.f);
		else
			_Player.GetPresence().SetXVel(0.f);

		_Player.Update(dt);

		if (_Player.GetPresence().GetX() > _Window->getSize().x - _Player.GetSize().GetWidth())
		{
			_Player.GetPresence().SetX(_Window->getSize().x - _Player.GetSize().GetWidth());
			_Player.Update(0.f);
		}
		else if (_Player.GetPresence().GetX() < 0.f)
		{
			_Player.GetPresence().SetX(0.f);
			_Player.Update(0.f);
		}

		if (_Player.GetPresence().GetY() > _Window->getSize().y - _Player.GetSize().GetHeight())
		{
			_Player.GetPresence().SetY(_Window->getSize().y - _Player.GetSize().GetHeight());
			_Player.Update(0.f);
		}
		else if (_Player.GetPresence().GetY() < 0.f)
		{
			_Player.GetPresence().SetY(0.f);
			_Player.Update(0.f);
		}

		//	Spawn Bullets
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (_ShootTimer >= _ShootDelay))
		{
			_ShootTimer = 0.f;

			Entity* bullet = new Entity();
			bullet->SetIcon(new AnimIcon(bullet, sf::Sprite(*_ImgMan.GetTexturePntr("PBullet")), _ImgMan.GetAnimation("PBullet_Idle")));
			bullet->GetSize().SetSize(16.f, 16.f);
			bullet->GetPresence().SetPosition(_Player.GetPresence().GetX() + ((_Player.GetSize().GetWidth() - bullet->GetSize().GetWidth()) / 2.f), _Player.GetPresence().GetY());
			bullet->GetPresence().SetVelocity(0.f, -200.f);

			_Bullets.AddEnt(bullet);
		}

		//	Update Bullets
		for (int i = 0; i < _Bullets.CountEnts(); i++)
		{
			Entity* ent = _Bullets.GetEnt(i);
			ent->Update(dt);

			if (ent->GetPresence().GetY() <= -ent->GetSize().GetHeight())
				_Bullets.DelEnt(ent);
		}

		//	Update Enemies
		for (int i = 0; i < _Enemies.CountEnts(); i++)
		{
			Entity* ent = _Enemies.GetEnt(i);
			ent->Update(dt);
			
			if (ent->GetPresence().GetY() > _Window->getSize().y)
				_Enemies.DelEnt(ent);
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
			if (GenBoundBox(_Enemies.GetEnt(e)).Intersects(GenBoundBox(&_Player)))
			{
				_Enemies.GetEnt(e)->SetAlive(false);
				_Player.SetAlive(false);
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
	_Player.Draw(_Window);

	for (int i = 0; i < _Bullets.CountEnts(); i++)
		_Bullets.GetEnt(i)->Draw(_Window);

	for (int i = 0; i < _Enemies.CountEnts(); i++)
		_Enemies.GetEnt(i)->Draw(_Window);


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
	rect.setPosition(ent->GetPresence().GetX(), ent->GetPresence().GetY());
	rect.setSize(sf::Vector2f(ent->GetSize().GetWidth(), ent->GetSize().GetHeight()));
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(col);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	win->draw(rect);
};