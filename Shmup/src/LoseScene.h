#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include "core/Scene.h"
#include "MenuList.h"

class LoseScene : public Scene
{
public:

	LoseScene(SDL_Renderer* renderer);
	~LoseScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	SDL_Renderer* _Window;
	TTF_Font* _Font;

	SDLMenuList _MenuList;
};