#ifndef HELP
#define HELP
#include <SFML\Graphics.hpp>

class Help
{
	sf::Font m_font; // font used
	sf::Text m_helpText; // text used to display help message on screen

public:
	Help(sf::Font & font);
	~Help();
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
	void processEvents(sf::Event & event);

};

#endif // !HELP