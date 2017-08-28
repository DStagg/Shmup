#ifndef SHOOTSCENE_H
#define SHOOTSCENE_H

#include "SFML\Graphics.hpp"
#include "Scene.h"
#include "Random.h"
#include "Entity.h"
#include "LoseScene.h"
#include "ImageManager.h"
#include "PopAnim.h"
#include "Factory.h"
#include "Level.h"
#include "SpawnQueue.h"

class ShootScene : public Scene
{
public:

	ShootScene(sf::RenderWindow* win);
	~ShootScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	sf::RenderWindow* _Window;

	float _ShootTimer = 0.f;
	float _ShootDelay = 0.25f;

	Level _Level;
	SpawnQueue _SpawnQueue;

	ImageManager _ImgMan;
};

void DebugDrawEntity(Entity* ent, sf::RenderWindow* rw, sf::Color col = sf::Color::Cyan);

#endif