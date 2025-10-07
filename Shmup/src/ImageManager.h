#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <iostream>

struct AnimationFrame
{
	AnimationFrame(int x, int y, int w, int h, float ft);

	int _X, _Y, _Width, _Height;
	float _FrameTime;
};

struct Animation
{
	Animation();

	void Play(float dt);
	AnimationFrame GetCurrFrame();

	bool _Loop;
	float _Rate;
	float _Time;
	int _CurrentFrame;
	std::vector<AnimationFrame> _Frames;
};

class ImageManager
{
public:

	ImageManager(SDL_Renderer* renderer);
	~ImageManager();

	bool LoadTextureFromFile(std::string tag, std::string filename);
	SDL_Texture* GetTexturePntr(std::string tag);

	void AddAnimation(std::string tag, Animation anim);
	Animation GetAnimation(std::string tag);

private:

	std::map<std::string, SDL_Texture*> _Textures;
	std::map<std::string, Animation> _Animations;
	SDL_Renderer* _Window;

};

SDL_FRect AnimIntoRect(Animation anim);