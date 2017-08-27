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

	void SetTransMask(sf::Color col = sf::Color(163, 73, 164));
	sf::Color GetTransMask();

	void SetSmooth(bool b);
	bool GetSmooth();

private:

	sf::Color _TransparencyMask;
	bool _Smooth;

	std::map<std::string, sf::Texture> _Textures;
};


#endif