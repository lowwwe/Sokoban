#include "Penguin.h"

#include "Colours.h"


Penguin::Penguin() :
	m_vertexes{ sf::Triangles,6 },
	m_footSteps{ sf::Triangles,MAX_FOOT_STEPS_6 },
	m_animationFrame{ 1 },
	m_perFrame{ sf::microseconds(100000) },
	m_intraFrameDelay{ sf::seconds(0) },
	m_position{},
	m_facing{ Direction::Down },
	m_stepstaken{ 0 },
	m_square{ 0,0 },
	m_leftFoot{ false },
	m_drowning{ false },
	m_drownStep{ 0 },
	m_alive{ true },
	m_ready{ true }

{
	sf::FloatRect textureCoOrds = TextureManager::getRect("penguin");
	m_texOffset = sf::Vector2f{ textureCoOrds.left, textureCoOrds.top };
	updateVertexes();
	updateTexCoords();	
	m_velocity = sf::Vector2f(0.0f, m_step);
	
	for (int i = 0; i < MAX_FOOT_STEPS_6; i++)
	{
		m_footSteps[i].color = FADE;
	}
}


Penguin::~Penguin()
{
}

bool Penguin::move(Direction direction)
{
	m_ready = false;
	m_facing = direction;
	m_stepstaken = NO_PENGUIN_STEPS;
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
		m_velocity = sf::Vector2f( m_step, 0.0f);
		m_square.y++;
		break;
	case Direction::Up:
		m_velocity = sf::Vector2f(0.0f, -m_step);
		m_square.x--;
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
			if (m_animationFrame == 0)
			{
				addFootStep();
			}
		}
		
		m_position += m_velocity;
		updateVertexes();
		if (m_stepstaken == 0)
		{
			m_ready = true;
		}
	}
	if (m_drowning)
	{
		if (--m_drownStep == 0)
		{
			m_alive = false;
		}
		m_position.y += 1;
		updateVertexesDrowning();
	}
}

void Penguin::position()
{
	m_position.x = TOP_LEFT.x + m_square.y * TILE_SIZE;
	m_position.y = TOP_LEFT.y + m_square.x * TILE_SIZE;
}

void Penguin::drown()
{
	m_drowning = true;
	m_drownStep = 26;
	m_ready = false;
	m_stepstaken = 0;
	m_position.y -= 8;
	m_vertexes[2].texCoords -= sf::Vector2f{ 0.0, 8.0f };
	m_vertexes[4].texCoords -= sf::Vector2f{ 0.0, 8.0f };
	m_vertexes[5].texCoords -= sf::Vector2f{ 0.0, 8.0f };
}


void Penguin::updateVertexesDrowning()
{
	float height =  static_cast<float>(m_drownStep);
	m_vertexes[0].position = m_position;
	m_vertexes[1].position = m_position + sf::Vector2f{ TILE_SIZE, 0.0f };
	m_vertexes[2].position = m_position + sf::Vector2f{ TILE_SIZE, height };
	m_vertexes[3].position = m_position;
	m_vertexes[4].position = m_position + sf::Vector2f{ TILE_SIZE, height };
	m_vertexes[5].position = m_position + sf::Vector2f{ 0.0f, height };
}

void Penguin::updateVertexes()
{
	
	m_vertexes[0].position = m_position;
	m_vertexes[1].position = m_position + sf::Vector2f{ TILE_SIZE, 0.0f};
	m_vertexes[2].position = m_position + sf::Vector2f{ TILE_SIZE, TILE_SIZE };
	m_vertexes[3].position = m_position;
	m_vertexes[4].position = m_position + sf::Vector2f{ TILE_SIZE, TILE_SIZE };
	m_vertexes[5].position = m_position + sf::Vector2f{ 0.0f, TILE_SIZE };
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

void Penguin::addFootStep()
{
	bool found{ false };
	m_noFootSteps = false;
	sf::Vector2f width{};
	sf::Vector2f height{};
	sf::Vector2f footPosition;
	int i{ 0 };
	while (i< MAX_FOOT_STEPS_6)
	{
		if (!found  && m_footSteps[i].color.a < 21) // fading by 10
		{
			if (m_facing == Direction::Up || m_facing == Direction::Down)
			{
				width.x = 4.0f;
				height.y = 8.0f;
				if (m_leftFoot)
				{
					footPosition = m_position + sf::Vector2f(10, 23);
				}
				else
				{
					footPosition = m_position + sf::Vector2f(16, 23);
				}				
			}
			else
			{
				width.x = 8.0f;
				height.y = 4.0f;
				if (m_leftFoot)
				{
					footPosition = m_position + sf::Vector2f(11, 20);
				}
				else
				{
					footPosition = m_position + sf::Vector2f(11, 25);
				}				
			}
			m_leftFoot = !m_leftFoot;
			found = true;
			m_footSteps[i].position = footPosition;
			m_footSteps[i].color = FOOT_TOP;
			m_footSteps[i+1].position = footPosition +width;
			m_footSteps[i+1].color = FOOT_TOP;
			m_footSteps[i+2].position = footPosition + width + height;
			m_footSteps[i+2].color = FOOT_BOTTOM;
			m_footSteps[i+3].position = footPosition;
			m_footSteps[i+3].color = FOOT_TOP;		
			m_footSteps[i+4].position = footPosition + width + height;
			m_footSteps[i+4].color = FOOT_BOTTOM;
			m_footSteps[i+5].position = footPosition + height;
			m_footSteps[i+5].color = FOOT_BOTTOM;
		}		
		i += 6;
	}
}

void Penguin::fadeFootSteps()
{
	if (!m_noFootSteps)
	{
		m_noFootSteps = true;
		for (size_t j = 0; j < MAX_FOOT_STEPS_6; j++)
		{
			if (m_footSteps[j].color.a > 1)
			{
				m_footSteps[j].color -= FADE;
				m_noFootSteps = false;
			}
		}
	}
}

void Penguin::reset()
{
	m_alive = true;
	m_drowning = false;
	m_animationFrame = 1;
	m_facing = Direction::Down;
	m_stepstaken = 0;		
	m_leftFoot = false;
	m_drownStep = 0;		
	m_ready= true;
}


