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

	Entity _Player;
	std::vector<Entity*> _Bullets;
	
	sf::RenderWindow* _Window;

	float _ShootTimer = 0.f;
	float _ShootDelay = 0.25f;
};

void DebugDrawEntity(Entity* ent, sf::RenderWindow* rw);

#endif