#ifdef __RELEASE__
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <SFML/Graphics.hpp>

#include "src/Scene.h"
#include "src/MenuScene.h"


int main()
{
	int FramesPerSecond = 60;
	float deltaT = 0.f;
	sf::Clock UpdateClock;

	sf::RenderWindow _Window;
	_Window.create(sf::VideoMode(624, 624), "Shoot-em-up");

	SceneManager SCM;
	SCM.PushScene(new MenuScene(&_Window));
	
	UpdateClock.restart();
	while (SCM.GetActiveScenePntr() != 0)
	{
		SCM.GetActiveScenePntr()->Update(UpdateClock.restart().asSeconds());
		_Window.clear();
		SCM.GetActiveScenePntr()->DrawScreen();
		_Window.display();
		SCM.CullScenes();
	}
	
	return 0;
}