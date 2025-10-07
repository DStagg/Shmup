#ifdef __RELEASE__
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "ext/Timer.h"

#include "src/core/Scene.h"
#include "src/MenuScene.h"

SDL_Window* _Window = nullptr;
SDL_Renderer* _Renderer = nullptr;
MIX_Mixer* _Mixer = nullptr;

int main()
{
	Timer UpdateClock;

	SDL_CreateWindowAndRenderer("Shoot-em-up", 624, 624, NULL, &_Window, &_Renderer);
	SDL_SetRenderDrawBlendMode(_Renderer, SDL_BLENDMODE_BLEND);
	SDL_SetDefaultTextureScaleMode(_Renderer, SDL_SCALEMODE_NEAREST);

	if (!TTF_Init())
	{
		std::cout << "Couldn't init SDL_TTF :" << SDL_GetError() << std::endl;
		return SDL_APP_FAILURE;
	}
	if (!MIX_Init())
	{
		const char* error = SDL_GetError();
		std::cout << "Couldn't init SDL_Mixer :" << error << std::endl;
		return SDL_APP_FAILURE;
	}

	_Mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

	if (!_Mixer)
	{
		const char* error = SDL_GetError();
		std::cout << "Couldn't create mixer : " << error << std::endl;
		return SDL_APP_FAILURE;
	}

	SceneManager SCM;
	SCM.PushScene(new MenuScene(_Renderer));
	
	UpdateClock.Reset();
	while (SCM.GetActiveScenePntr() != 0)
	{
		SCM.GetActiveScenePntr()->Update(UpdateClock.Lap() / 1000.f);

		SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 255);
		SDL_RenderClear(_Renderer);
		SCM.GetActiveScenePntr()->DrawScreen();
		SDL_RenderPresent(_Renderer);
		SCM.CullScenes();
	}
	
	MIX_DestroyMixer(_Mixer);
	MIX_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(_Renderer);
	SDL_DestroyWindow(_Window);
	SDL_Quit();

	return SDL_APP_SUCCESS;
}