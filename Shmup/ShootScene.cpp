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
	
	AnimationFrame f(0, 0, 16, 16, 0.2f);
	Animation anim;
	anim._Frames.push_back(f);
	AnimationFrame f2(16, 0, 16, 16, 0.2f);
	anim._Frames.push_back(f2);
	AnimationFrame f3(32, 0, 16, 16, 0.2f);
	anim._Frames.push_back(f3);
	AnimationFrame f4(48, 0, 16, 16, 0.2f);
	anim._Frames.push_back(f4);
	_ImgMan.AddAnimation("PBullet_Idle", anim);

	AnimationFrame p1(0, 0, 48, 27, 0.2f);
	AnimationFrame p2(48, 0, 48, 27, 0.2f);
	AnimationFrame p3(96, 0, 48, 27, 0.2f);
	Animation panim;
	panim._Frames.push_back(p1);
	panim._Frames.push_back(p2);
	panim._Frames.push_back(p3);
	_ImgMan.AddAnimation("Player_Idle", panim);

	AnimationFrame e1(0, 0, 32, 32, 0.3f);
	AnimationFrame e2(32, 0, 32, 32, 0.3f);
	AnimationFrame e3(64, 0, 32, 32, 0.3f);
	Animation eanim;
	eanim._Frames.push_back(e1);
	eanim._Frames.push_back(e2);
	eanim._Frames.push_back(e3);
	eanim._Frames.push_back(e3);
	eanim._Frames.push_back(e2);
	eanim._Frames.push_back(e1);
	_ImgMan.AddAnimation("BombEnemy_Idle", eanim);

	_Player.SetSize(64.f, 32.f);
	_Player.SetPosition((_Window->getSize().x - _Player.GetWidth()) / 2.f, _Window->getSize().y - _Player.GetHeight());

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

			PlayerEnt* ent = new PlayerEnt();
			//ent->SetIcon(new RectIcon(ent, sf::Color::Red));
			ent->SetIcon(new AnimIcon(ent, sf::Sprite(*_ImgMan.GetTexturePntr("BombEnemy")), _ImgMan.GetAnimation("BombEnemy_Idle")));
			ent->SetVelocity(0.f, 100.f);
			ent->SetSize(50.f, 50.f);
			ent->SetPosition((float)Random::Generate(0, (int)(_Window->getSize().x - 50.f)), 0.f - 50.f);
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

		_Player.DoUpdate(dt);

		//	Spawn Bullets
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (_ShootTimer >= _ShootDelay))
		{
			_ShootTimer = 0.f;

			PlayerEnt* bullet = new PlayerEnt();
			bullet->SetIcon(new AnimIcon(bullet, sf::Sprite(*_ImgMan.GetTexturePntr("PBullet")), _ImgMan.GetAnimation("PBullet_Idle")));
			bullet->SetSize(16.f, 16.f);
			bullet->SetPosition(_Player.GetX() + ((_Player.GetWidth() - bullet->GetWidth()) / 2.f), _Player.GetY());
			bullet->SetVelocity(0.f, -200.f);

			_Bullets.AddEnt(bullet);
		}

		//	Update Bullets
		for (int i = 0; i < _Bullets.CountEnts(); i++)
		{
			PlayerEnt* ent = (PlayerEnt*)_Bullets.GetEnt(i);
			ent->DoUpdate(dt);

			if (ent->GetY() <= -ent->GetHeight())
				_Bullets.DelEnt(ent);
		}

		//	Update Enemies
		for (int i = 0; i < _Enemies.CountEnts(); i++)
		{
			PlayerEnt* ent = (PlayerEnt*)_Enemies.GetEnt(i);
			ent->DoUpdate(dt);
			
			if (ent->GetY() > _Window->getSize().y)
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
	_Player.DoDraw(_Window);

	for (int i = 0; i < _Bullets.CountEnts(); i++)
		_Bullets.GetEnt(i)->DoDraw(_Window);

	for (int i = 0; i < _Enemies.CountEnts(); i++)
		_Enemies.GetEnt(i)->DoDraw(_Window);

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