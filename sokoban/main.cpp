#include "main.h"
#include "Game.h"
#include "TextureManager.h"
#include <SFML\Graphics.hpp>
#include <iostream>

int main()
{
	sf::Font font;
	if (!font.loadFromFile("ASSETS\\FONTS\\Android.ttf"))
	{
		std::cout << "Problem with font" << std::endl;
	}
	TextureManager::loadData();
	Game game{font};
	//TextureManager m_atlasManager;
	
	
	game.run();
	return 1;

}