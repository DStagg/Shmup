#include "MenuScene.h"

MenuScene::MenuScene(sf::RenderWindow* rw)
{
	_Window = rw;
};
MenuScene::~MenuScene()
{

};

void MenuScene::Begin()
{
	_Font.loadFromFile("Roboto-Regular.ttf");
	Service::Init(new SFMLAudio());

	_MenuList.Populate({ "Play","Quit" });
	_MenuList.Format(_Font, _Window->getSize().x / 2.f, _Window->getSize().y / 2.f, SFMLMenuList::Center);
	_MenuList.SetBuffers(10.f, 50.f);

	if (Service::GetAudio().StoreStream("MainBGM", "Paradox.ogg"))
		Service::GetAudio().PlayStream("MainBGM");
};

void MenuScene::End()
{

};

void MenuScene::Pause()
{

};

void MenuScene::Resume()
{

};

void MenuScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			GetManager()->Quit();
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			GetManager()->Quit();
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
		{
			switch (_MenuList.GetChoice())
			{
			case 0:
				GetManager()->PushScene(new ShootScene(_Window));
				break;
			case 1:
				GetManager()->Quit();
				break;
			default:
				break;
			}
		}
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W))
			_MenuList.DecChoice();
		else if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S))
			_MenuList.IncChoice();

	}

};

void MenuScene::DrawScreen()
{
	_MenuList.Draw(_Window);
};