#ifndef BUCKET
#define BUCKET

#include <SFML\Graphics.hpp>
#include "Enums.h"
#include "TextureManager.h"

class Bucket
{
public:
	Bucket(sf::Vector2i square, int type);
	~Bucket();
	bool m_alive;
	sf::Vertex m_vertexes[6];
	bool update(sf::Time deltaTime);
	sf::Vector2i m_square;
	int m_foregroundItem;
	void initialise(sf::Vector2i square, Direction direction, int bucketType);
	void move(Direction direction);

private:
	float m_step = TILE_SIZE / NO_PLAYER_STEPS; // distance traveled per update
	sf::Vector2f m_texOffset; //offset into the texture atlas for penguim sprite sheet(sub)
	int m_stepstaken; // no of taken so far while moving one square
	sf::Vector2f m_position;
	int m_bucketNo;
	void position(); 
	void updateVertexes();
	void updateTexCoords();
	sf::Vector2f m_velocity; // displacement for sprite per update
	
};

#endif // !BUCKET