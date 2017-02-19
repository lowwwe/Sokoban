#include "TextureManager.h"
#include <iostream>
#include <string>
#include <fstream>


sf::Texture TextureManager::texture{};
std::vector<SpritInfo> TextureManager::m_atlas;

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

 sf::FloatRect TextureManager::getRect(std::string name)
{
	for each (SpritInfo var in TextureManager::m_atlas)
	{
		if (name == var.name)
		{
			return var.coOrds;
		}
	}
	return sf::FloatRect();
}

 void TextureManager::loadData()
{
	std::ifstream infile;
	std::string name;
	std::string equals;
	sf::IntRect coords;
	float x, y, width, height;
	infile.open("ASSETS\\IMAGES\\ATLAS.TXT");
	while (!infile.eof())
	{
		infile >> name >> equals >> x >> y >> width >> height;
		TextureManager::m_atlas.push_back({ name, sf::FloatRect{x,y,width, height} });
	}
	infile.close();
	if (!TextureManager::texture.loadFromFile("ASSETS\\IMAGES\\ATLAS.PNG"))
	{
		std::cout << "problem loading atlas" << std::endl;
	}

}
