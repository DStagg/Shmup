#ifndef LOSESCENE_H
#define LOSESCENE_H

#include "Scene.h"
#include "SFML\Graphics.hpp"
#include "MenuList.h"

class LoseScene : public Scene
{
public:

	LoseScene(sf::RenderWindow* rw);
	~LoseScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	sf::RenderWindow* _Window;
	sf::Font _Font;

	SFMLMenuList _MenuList;
};

#endif