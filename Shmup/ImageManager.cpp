#include "ImageManager.h"

ImageManager::ImageManager()
{
	sf::Texture defTex;
	defTex.create(32, 32);
	_Textures["Default"] = defTex;
	SetTransMask();
	SetSmooth(false);
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