#ifndef ARTIST_TEXT
#define ARTIST_TEXT


#include <SFML\Graphics\Text.hpp>

class ArtistText :
	public sf::Text
{
public:
	ArtistText();
	~ArtistText();
	int m_frameNo;
	int m_maxFrames;
	bool m_active;
	void m_nextFrame();

};

#endif // !ARTIST_TEXT