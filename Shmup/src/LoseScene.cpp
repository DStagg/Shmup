#include "LoseScene.h"

LoseScene::LoseScene(SDL_Renderer* renderer)
{
	_Window = renderer;
};
LoseScene::~LoseScene()
{

};

void LoseScene::Begin()
{
	_Font.loadFromFile("Roboto-Regular.ttf");

	_MenuList.Populate({ "Quit" });
	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	_MenuList.Format(_Font, (float)w / 2.f, (float)h / 2.f, SDLMenuList::Center);
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