#ifndef SHOOTSCENE_H
#define SHOOTSCENE_H

#include "SFML\Graphics.hpp"
#include "Scene.h"

#include "Entity.h"

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
};

void DebugDrawEntity(Entity* ent, sf::RenderWindow* rw);

#endif