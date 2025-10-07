#include "ImageManager.h"

AnimationFrame::AnimationFrame(int x, int y, int w, int h, float ft)
{
	_X = x;
	_Y = y;
	_Width = w;
	_Height = h;
	_FrameTime = ft;
};

Animation::Animation()
{
	_CurrentFrame = 0;
	_Time = 0.f;
	_Rate = 1.f;
	_Loop = true;
};

void Animation::Play(float dt)
{
	dt = dt * _Rate;
	_Time += dt;
	if (_Time >= GetCurrFrame()._FrameTime)
	{
		if ((_CurrentFrame < (int)_Frames.size() - 1) || (_Loop))
		{
			_Time -= GetCurrFrame()._FrameTime;
			_CurrentFrame++;

			if ((_CurrentFrame >= (int)_Frames.size()) && (_Loop))
				_CurrentFrame = 0;
		}
	}
};

AnimationFrame Animation::GetCurrFrame()
{
	return _Frames[_CurrentFrame];
};

ImageManager::ImageManager(SDL_Renderer* renderer)
{
	_Window = renderer;

	SDL_Texture* texture = SDL_CreateTexture(_Window, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 32, 32);
	SDL_Surface* surface = nullptr;

	if (SDL_LockTextureToSurface(texture, NULL, &surface)) {
		SDL_FillSurfaceRect(surface, NULL, SDL_MapRGB(SDL_GetPixelFormatDetails(surface->format), NULL, 0,0,0));  /* make the whole surface black */
		SDL_UnlockTexture(texture);
	}
	_Textures["Default"] = texture;

	AnimationFrame frame(0, 0, 1, 1, 0.f);
	Animation anim;
	anim._Frames.push_back(frame);
	_Animations["Default"] = anim;
};
ImageManager::~ImageManager()
{
	for (std::map<std::string, SDL_Texture*>::iterator i = _Textures.begin(); i != _Textures.end(); i++)
		SDL_DestroyTexture(i->second);
};

bool ImageManager::LoadTextureFromFile(std::string tag, std::string filename)
{
	if (!_Window) return false;

	SDL_Texture* new_text = IMG_LoadTexture(_Window, filename.c_str());
	if (!new_text)
	{
		_Textures.insert_or_assign(tag, _Textures["Default"]);
		std::cout << "Failed to load " << filename << std::endl;
		return false;
	}
	
	_Textures.insert_or_assign(tag, new_text);
	return true;
};

SDL_Texture* ImageManager::GetTexturePntr(std::string tag)
{
	for (std::map<std::string, SDL_Texture*>::iterator i = _Textures.begin(); i != _Textures.end(); i++)
	{
		if (i->first == tag)
			return i->second;
	}

	return _Textures["Default"];
};

void ImageManager::AddAnimation(std::string tag, Animation anim)
{
	_Animations[tag] = anim;
};
Animation ImageManager::GetAnimation(std::string tag)
{
	for (std::map<std::string, Animation>::iterator i = _Animations.begin(); i != _Animations.end(); i++)
	{
		if (i->first == tag)
			return _Animations[tag];
	}

	return _Animations["Default"];
};

///

SDL_FRect AnimIntoRect(Animation anim)
{
	SDL_FRect rec;
	rec.x = anim._Frames[anim._CurrentFrame]._X;
	rec.y = anim._Frames[anim._CurrentFrame]._Y;
	rec.w = anim._Frames[anim._CurrentFrame]._Width;
	rec.h = anim._Frames[anim._CurrentFrame]._Height;
	return rec;
};