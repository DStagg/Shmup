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
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_EVENT_QUIT)
			GetManager()->Quit();
		else if ((e.type == SDL_EVENT_KEY_DOWN) && ((e.key.key == SDLK_ESCAPE) || (e.key.key == SDLK_RETURN)))
			GetManager()->Quit();
	}
};
void LoseScene::DrawScreen()
{
	GetParent()->DrawScreen();
	_MenuList.Draw(_Window);
};