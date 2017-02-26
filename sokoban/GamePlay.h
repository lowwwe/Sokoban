#ifndef GAMEPLAY
#define GAMEPLAY

#include "TextureManager.h"
#include "Penguin.h"
#include "Player.h"
#include "Bucket.h"


const int ICE_POOL = 22;
const int BUCKET1 = 2;
const int BUCKET2 = 3;
const int BUCKET3 = 21;
const int TILES_WIDE = 16;
const int TILES_HIGH = 16;
const int GRIDSIZE = 5;






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
	void setupBaseItemsVertexes(sf::Vector2f targetOffset);
	void loadItemsFile();
	void setupItemsVertexes();
	void addPenguinVertexes(int index);
	void setupNavigation();
	void setupTexture();
	void setupBuckets();
	void addBucketVertexes();
	void playerMovement();
	void moveBucket(sf::Vector2i square, Direction direction);
	void updateBuckets(sf::Time deltaTime);
	Direction newDirection(Direction default);
	
	sf::RenderTexture m_newTexture;
	sf::VertexArray m_background;
	sf::VertexArray m_foreground;
	sf::Font m_font;
	sf::FloatRect m_textureCoOrds;
	Penguin m_penguins[MAX_PENGUIN];
	Player m_player;
	std::vector<Bucket> m_buckets;
	sf::VertexArray m_penguinVertexes;

	int m_baseLevel[TILES_WIDE][TILES_HIGH];
	int m_itemsLevel[TILES_WIDE][TILES_HIGH];
	bool m_navigation[TILES_WIDE][TILES_HIGH];
	sf::Time m_timer;
	sf::Text m_clock;

};

#endif // !GAMEPLAY