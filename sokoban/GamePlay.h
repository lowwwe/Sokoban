#ifndef GAMEPLAY
#define GAMEPLAY

#include "TextureManager.h"

#define TILES_WIDE 16
#define TILES_HIGH 16
const float TILE_SIZE{ 32.0f };

const sf::Vector2f TOP_LEFT{ 32.0f,32.0f };

class GamePlay
{
public:
	GamePlay(sf::Font & font);
	~GamePlay();
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
	void processEvents(sf::Event & event);
private:
	void setupLevel();
	void loadFile();
	void setupVertexes();
	sf::VertexArray m_base;
	sf::Font m_font;
	
	

	int m_baseLevel[TILES_WIDE][TILES_HIGH];
};

#endif // !GAMEPLAY