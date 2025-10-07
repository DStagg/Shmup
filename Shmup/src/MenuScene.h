#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "core/Scene.h"
#include "core/Service.h"
#include "MenuList.h"
#include "ShootScene.h"

class MenuScene : public Scene
{
public:

	MenuScene(SDL_Renderer* renderer, MIX_Mixer* mix);
	~MenuScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	SDL_Renderer* _Window;
	SDLMenuList _MenuList;
	TTF_Font* _Font;
	MIX_Mixer* _Mixer;
};