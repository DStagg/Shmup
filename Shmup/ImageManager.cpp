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
};

ImageManager::ImageManager()
{
	sf::Texture defTex;
	defTex.create(32, 32);
	_Textures["Default"] = defTex;
	SetTransMask();
	SetSmooth(false);

	AnimationFrame frame(0, 0, 1, 1, 0.f);
	Animation anim;
	anim._Frames.push_back(frame);
	_Animations["Default"] = anim;
};
ImageManager::~ImageManager()
{

};

bool ImageManager::LoadTextureFromFile(std::string tag, std::string filename)
{
	sf::Image img;
	sf::Texture tex;

	if (img.loadFromFile(filename))
	{
		img.createMaskFromColor(GetTransMask());
		tex.loadFromImage(img);
		tex.setSmooth(GetSmooth());
		_Textures[tag] = tex;
		return true;
	}

	tex.create(32, 32);
	_Textures[tag] = tex;
	return false;
};

sf::Texture* ImageManager::GetTexturePntr(std::string tag)
{
	for (std::map<std::string, sf::Texture>::iterator i = _Textures.begin(); i != _Textures.end(); i++)
	{
		if (i->first == tag)
			return &_Textures[tag];
	}

	return &_Textures["Default"];
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

void ImageManager::SetTransMask(sf::Color col)
{
	_TransparencyMask = col;
};
sf::Color ImageManager::GetTransMask()
{
	return _TransparencyMask;
};

void ImageManager::SetSmooth(bool b)
{
	_Smooth = b;
};
bool ImageManager::GetSmooth()
{
	return _Smooth;
};