#include "LoseScene.h"

LoseScene::LoseScene(sf::RenderWindow* rw)
{
	_Window = rw;
};
LoseScene::~LoseScene()
{

};

void LoseScene::Begin()
{
	_Font.loadFromFile("Roboto-Regular.ttf");

	_MenuList.Populate({ "Quit" });
	_MenuList.Format(_Font, _Window->getSize().x / 2.f, _Window->getSize().y / 2.f, SFMLMenuList::Center);
	_MenuList.SetBuffers(0.f, 0.f);
};
void LoseScene::End()
{

};
void LoseScene::Pause()
{

};
void LoseScene::Resume()
{

};
void LoseScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			GetManager()->Quit();
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			GetManager()->Quit();
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
			GetManager()->Quit();
	}
};
void LoseScene::DrawScreen()
{
	GetParent()->DrawScreen();
	_MenuList.Draw(_Window);
};