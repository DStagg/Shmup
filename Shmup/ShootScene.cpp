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
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			SetRunning(false);


	}
};
void ShootScene::DrawScreen()
{
	Entity ent;
	ent.SetPosition(100.f, 100.f);
	ent.SetSize(100.f, 100.f);
	DebugDrawEntity(&ent, _Window);
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