#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* renderer)
{
	_Window = renderer;
};
MenuScene::~MenuScene()
{

};

void MenuScene::Begin()
{
	_Font.loadFromFile("Roboto-Regular.ttf");
	Service::Init(new SFMLAudio());

	_MenuList.Populate({ "Play","Quit" });
	int w, h;
	SDL_GetRenderOutputSize(_Window, &w, &h);
	_MenuList.Format(_Font, (float)w / 2.f, (float)h / 2.f, SDLMenuList::Center);
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
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT)
			GetManager()->Quit();
		else if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_ESCAPE))
			GetManager()->Quit();
		else if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_RETURN))
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
		else if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_W))
			_MenuList.DecChoice();
		else if ((e.type == SDL_EVENT_KEY_DOWN) && (e.key.key == SDLK_S))
			_MenuList.IncChoice();

	}

};

void MenuScene::DrawScreen()
{
	_MenuList.Draw(_Window);
};