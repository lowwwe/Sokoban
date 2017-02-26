#include "Bucket.h"



Bucket::Bucket(sf::Vector2i square, int type)
	: m_square{square},
	m_bucketNo{type},
	m_stepstaken{ 0 }
{
	sf::FloatRect textureCoOrds = TextureManager::getRect("tiles");
	m_texOffset = sf::Vector2f{ textureCoOrds.left + (type % 5)*TILE_SIZE, textureCoOrds.top + (type / 5)* TILE_SIZE};
	position();
	updateVertexes();
	updateTexCoords();
}


Bucket::~Bucket()
{
}

bool Bucket::update(sf::Time deltaTime)
{
	if (m_stepstaken > 0)
	{
		--m_stepstaken;		
		m_position += m_velocity;
		updateVertexes();
		if (m_stepstaken == 0)
		{
			return(true);
		}
	}
	return false;
}

void Bucket::initialise(sf::Vector2i square, Direction direction, int bucketType)
{
}

void Bucket::move(Direction direction)
{	
	m_stepstaken = NO_PLAYER_STEPS;
	switch (direction)
	{
	case Direction::Down:
		m_velocity = sf::Vector2f(0.0f, m_step);
		m_square.x++;
		break;
	case Direction::Left:
		m_velocity = sf::Vector2f(-m_step, 0.0f);
		m_square.y--;
		break;
	case Direction::Right:
		m_velocity = sf::Vector2f(m_step, 0.0f);
		m_square.y++;
		break;
	case Direction::Up:
		m_velocity = sf::Vector2f(0.0f, -m_step);
		m_square.x--;
		break;
	default:
		break;
	}
}

void Bucket::position()
{
	m_position.x = TOP_LEFT.x + m_square.y * TILE_SIZE;
	m_position.y = TOP_LEFT.y + m_square.x * TILE_SIZE;
}

void Bucket::updateVertexes()
{
	m_vertexes[0].position = m_position;
	m_vertexes[1].position = m_position + sf::Vector2f{ TILE_SIZE, 0.0f };
	m_vertexes[2].position = m_position + sf::Vector2f{ TILE_SIZE, TILE_SIZE };
	m_vertexes[3].position = m_position;
	m_vertexes[4].position = m_position + sf::Vector2f{ TILE_SIZE, TILE_SIZE };
	m_vertexes[5].position = m_position + sf::Vector2f{ 0.0f, TILE_SIZE };
}

void Bucket::updateTexCoords()
{
	m_vertexes[0].texCoords = m_texOffset ;
	m_vertexes[1].texCoords = m_texOffset + sf::Vector2f{ TILE_SIZE, 0.0f };
	m_vertexes[2].texCoords = m_texOffset + sf::Vector2f{ TILE_SIZE, TILE_SIZE };
	m_vertexes[3].texCoords = m_texOffset ;
	m_vertexes[4].texCoords = m_texOffset + sf::Vector2f{ TILE_SIZE, TILE_SIZE };
	m_vertexes[5].texCoords = m_texOffset + sf::Vector2f{ 0.0f, TILE_SIZE };
}
