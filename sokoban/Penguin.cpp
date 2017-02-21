#include "Penguin.h"
#include "TextureManager.h"



Penguin::Penguin() :
	m_vertexes{ sf::Triangles,6 },
	m_animationFrame{ 1 },
	m_perFrame{ sf::microseconds(100000) },
	m_intraFrameDelay{ sf::seconds(0) },
	m_position{ 144,112 },
	m_facing{ Direction::Down },
	m_stepstaken{ 0 },
	m_square{1,1}
{
	sf::FloatRect textureCoOrds = TextureManager::getRect("penguin");
	m_texOffset = sf::Vector2f{ textureCoOrds.left, textureCoOrds.top };
	updateVertexes();
	updateTexCoords();
	m_velocity = sf::Vector2f(0.0f, m_step);
	m_position.x = 16 + m_square.x * TILE_SIZE;
	m_position.y = 16 + m_square.y * TILE_SIZE;
}


Penguin::~Penguin()
{
}

bool Penguin::move(Direction direction)
{
	m_ready = false;
	m_facing = direction;
	m_stepstaken = NO_STEPS;
	switch (direction)
	{
	case Direction::Down:
		m_velocity = sf::Vector2f(0.0f, m_step);
		m_square.x++;
		m_position.x = 16 + m_square.x * TILE_SIZE;
		break;
	case Direction::Left:
		m_velocity = sf::Vector2f(-m_step, 0.0f);
		break;
	case Direction::Right:
		m_velocity = sf::Vector2f( m_step, 0.0f);
		break;
	case Direction::Up:
		m_velocity = sf::Vector2f(0.0f, -m_step);
		break;
	default:
		break;
	}
	return false;
}

void Penguin::update(sf::Time deltaTime)
{
	if (m_stepstaken > 0)
	{
		--m_stepstaken;
		m_intraFrameDelay += deltaTime;

		if (m_intraFrameDelay > m_perFrame)
		{
			m_intraFrameDelay -= m_perFrame;
			m_animationFrame = ++m_animationFrame % FRAMES;
			updateTexCoords();
		}

		m_position += m_velocity;
		updateVertexes();
		if (m_stepstaken == 0)
		{
			m_ready = true;
		}
	}
}

void Penguin::updateVertexes()
{
	
	m_vertexes[0].position = m_position;
	m_vertexes[1].position = m_position + sf::Vector2f{32.0f, 0.0f};
	m_vertexes[2].position = m_position + sf::Vector2f{ 32.0f, 32.0f };
	m_vertexes[3].position = m_position;
	m_vertexes[4].position = m_position + sf::Vector2f{ 32.0f, 32.0f };
	m_vertexes[5].position = m_position + sf::Vector2f{ 0.0f, 32.0f };	
}

void Penguin::updateTexCoords()
{
	m_vertexes[0].texCoords = m_texOffset + sf::Vector2f{ TILE_SIZE * m_animationFrame, static_cast<int>(m_facing) * TILE_SIZE };
	m_vertexes[1].texCoords = m_texOffset + sf::Vector2f{ TILE_SIZE * m_animationFrame + TILE_SIZE, static_cast<int>(m_facing) * TILE_SIZE };
	m_vertexes[2].texCoords = m_texOffset + sf::Vector2f{ TILE_SIZE * m_animationFrame + TILE_SIZE, static_cast<int>(m_facing) * TILE_SIZE + TILE_SIZE };
	m_vertexes[3].texCoords = m_texOffset + sf::Vector2f{ TILE_SIZE * m_animationFrame, static_cast<int>(m_facing) * TILE_SIZE };
	m_vertexes[4].texCoords = m_texOffset + sf::Vector2f{ TILE_SIZE * m_animationFrame + TILE_SIZE, static_cast<int>(m_facing) * TILE_SIZE + TILE_SIZE };
	m_vertexes[5].texCoords = m_texOffset + sf::Vector2f{ TILE_SIZE * m_animationFrame , static_cast<int>(m_facing) * TILE_SIZE + TILE_SIZE };
}


