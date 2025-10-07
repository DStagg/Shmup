#pragma once

#include <SDL3/SDL.h>
#include "core/Scene.h"
#include "core/Random.h"
#include "Entity.h"
#include "LoseScene.h"
#include "ImageManager.h"
#include "PopAnim.h"
#include "Factory.h"
#include "Level.h"
#include "SpawnQueue.h"
#include "PlayerEnt.h"
#include "core/Service.h"
#include "AudioService.h"

class ShootScene : public Scene
{
public:

	ShootScene(SDL_Renderer* renderer, MIX_Mixer* mix);
	~ShootScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	SDL_Renderer* _Window;

	float _ShootTimer = 0.f;
	float _ShootDelay = 0.25f;

	Level _Level;
	SpawnQueue _SpawnQueue;
	MIX_Mixer* _Mixer;
	ImageManager* _ImgMan;
};

void DebugDrawEntity(Entity* ent, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);