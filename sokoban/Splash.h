#ifndef SPLASH
#define SPLASH

#include <SFML\Graphics.hpp>

class Splash
{
public:
	Splash(sf::Font & font);
	~Splash();
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
	void processEvents(sf::Event & event);
private:
	sf::Font m_font; // font used
	sf::Text m_promptText; // text used to display licence message on screen
	sf::VertexArray m_background;	
	
	bool m_keypressed;
};

#endif // !SPLASH