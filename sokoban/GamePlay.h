#ifndef GAMEPLAY
#define GAMEPLAY

#include "TextureManager.h"
#include "Penguin.h"

#define TILES_WIDE 16
#define TILES_HIGH 16
#define GRIDSIZE 5
#define MAX_PENGUINS 5



const sf::Vector2f TOP_LEFT{ 16.0f,16.0f };

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
	void loadBaseFile();
	void setupBaseVertexes(sf::Vector2f targetOffset);
	void loadItemsFile();
	void setupItemsVertexes();
	void addPenguinVertexes();
	void setupNavigation();
	void setupTexture();

	Direction newDirection(Direction default);
	
	sf::RenderTexture m_newTexture;
	sf::VertexArray m_background;
	sf::VertexArray m_foreground;
	sf::Font m_font;
	sf::FloatRect m_textureCoOrds;
	Penguin m_penguins[MAX_PENGUINS];
	sf::VertexArray m_penguinVertexes;

	int m_baseLevel[TILES_WIDE][TILES_HIGH];
	int m_itemsLevel[TILES_WIDE][TILES_HIGH];
	bool m_navigation[TILES_WIDE][TILES_HIGH];
};

#endif // !GAMEPLAY