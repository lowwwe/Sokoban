#include "main.h"
#include "Game.h"
#include <SFML\Graphics.hpp>
#include <iostream>

int main()
{
	sf::Font font;
	if (!font.loadFromFile("ASSETS\\FONTS\\Android.ttf"))
	{
		std::cout << "Problem with font" << std::endl;
	}
	Game game{font};
	game.run();
	return 1;

}