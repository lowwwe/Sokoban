#ifndef CREDITS
#define CREDITS
#include <SFML\Graphics.hpp>
#include "ArtistText.h"
#include <iostream>
#include <fstream>

class Game;

class Credits
{
public:
	Credits(sf::Font font);
	~Credits();
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	void processEvents(sf::Event & event);
private:	
	sf::Time m_cumulativeTime;
	sf::Font m_comicSans;
	ArtistText m_creditLines[20];	
	sf::Transform m_translation;
	bool m_offset;
	
	int m_exitSpeed;
	const int MAX_LINES = 20;
	bool m_fileOpen;
	std::ifstream m_artistsFile;
	bool m_blankLine;
	bool readNextLine(int index, int maxOffset);
	float m_offsetStep;
	
};

#endif // !CREDITS