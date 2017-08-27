#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "SFML\Graphics.hpp"
#include <algorithm>

class ImageManager
{
public:

	ImageManager();
	~ImageManager();

	bool LoadTextureFromFile(std::string tag, std::string filename);
	sf::Texture* GetTexturePntr(std::string tag);

private:

	std::map<std::string, sf::Texture> _Textures;
};


#endif