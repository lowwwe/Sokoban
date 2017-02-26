#ifndef BUCKET
#define BUCKET

#include <SFML\Graphics.hpp>
#include "Enums.h"
#include "TextureManager.h"

class Bucket
{
public:
	Bucket();
	~Bucket();
	bool m_alive;
	sf::Vertex m_vertexs[6];
	bool update(sf::Time deltaTime);
	sf::Vector2i m_square;
	int m_foregroundItem;
	void initialise(sf::Vector2i square, Direction direction, int bucketType);
private:
	float m_step = TILE_SIZE / NO_PLAYER_STEPS; // distance traveled per update
	sf::Vector2f m_texOffset; //offset into the texture atlas for penguim sprite sheet(sub)
	int m_stepstaken; // no of taken so far while moving one square
	sf::Vector2f m_position;
	
};

#endif // !BUCKET