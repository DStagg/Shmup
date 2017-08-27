#include "ImageManager.h"

ImageManager::ImageManager()
{
	sf::Texture defTex;
	defTex.create(32, 32);
	_Textures["Default"] = defTex;
};
ImageManager::~ImageManager()
{

};

bool ImageManager::LoadTextureFromFile(std::string tag, std::string filename)
{
	sf::Texture tex;
	if (tex.loadFromFile(filename))
	{
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