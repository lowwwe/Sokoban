#ifndef LICENCE
#define LICENCE

#include <SFML\Graphics.hpp>

class Licence
{
public:
	Licence(sf::Font & font);
	~Licence();
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
private:
	sf::Font m_font; // font used
	sf::Text m_licenceText; // text used to display licence message on screen
	sf::Time m_delay; // timer used to countdown delay
};

#endif // !LICENCE