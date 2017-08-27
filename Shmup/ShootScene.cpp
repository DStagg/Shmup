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
		_Bullets.push_back(bullet);
	}

	for (int i = 0; i < (int)_Bullets.size(); i++)
	{
		_Bullets[i]->SetX(_Bullets[i]->GetX() + (_Bullets[i]->GetXVel() * dt));
		_Bullets[i]->SetY(_Bullets[i]->GetY() + (_Bullets[i]->GetYVel() * dt));
	}

	while ((int)_Bullets.size() > 100)
		_Bullets.erase(_Bullets.begin());
};
void ShootScene::DrawScreen()
{
	DebugDrawEntity(&_Player, _Window);

	for (int i = 0; i < (int)_Bullets.size(); i++)
		DebugDrawEntity(_Bullets[i], _Window);
};

///

void DebugDrawEntity(Entity* ent, sf::RenderWindow* win)
{
	sf::RectangleShape rect;
	rect.setPosition(ent->GetX(), ent->GetY());
	rect.setSize(sf::Vector2f(ent->GetWidth(), ent->GetHeight()));
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(sf::Color::Cyan);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	win->draw(rect);
};