#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"
#include "Service.h"
#include "MenuList.h"
#include "ShootScene.h"

class MenuScene : public Scene
{
public:

	MenuScene(sf::RenderWindow* rw);
	~MenuScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	sf::RenderWindow* _Window;
	SFMLMenuList _MenuList;
	sf::Font _Font;
};

#endif