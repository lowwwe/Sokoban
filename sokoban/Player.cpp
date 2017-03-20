#include "Player.h"



Player::Player() :
	m_playerNo{ 0 },
	m_vertexes{ sf::Triangles, 6 },
	m_footSteps{ sf::Triangles,MAX_FOOT_STEPS_6 },
	m_animationFrame{ 1 },
	m_perFrame{ sf::microseconds(100000) },
	m_intraFrameDelay{ sf::seconds(0) },
	m_position{},
	m_facing{ Direction::Down },
	m_stepstaken{ 0 },
	m_square{ 5,5 },
	m_leftFoot{ false },
	m_female{false},
	m_ready{ true }
{
	sf::FloatRect textureCoOrds = TextureManager::getRect("characters");
	m_texOffset = sf::Vector2f{ textureCoOrds.left, textureCoOrds.top };
	updateVertexes();
	updateTexCoords();
	position();
	
	for (int i = 0; i < MAX_FOOT_STEPS_6; i++)
	{
		m_footSteps[i].color = FADE;
	}
}


Player::~Player()
{
}

bool Player::move(Direction direction)
{
	m_ready = false;
	m_facing = direction;
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
	return false;
}

void Player::update(sf::Time deltaTime)
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
}

void Player::position()
{
	m_position.x = TOP_LEFT.x + m_square.y * TILE_SIZE;
	m_position.y = TOP_LEFT.y + m_square.x * TILE_SIZE;
	updateVertexes();
}

void Player::fadeFootSteps()
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

void Player::updateVertexes()
{
	m_vertexes[0].position = m_position;
	m_vertexes[1].position = m_position + sf::Vector2f{ TILE_SIZE, 0.0f };
	m_vertexes[2].position = m_position + sf::Vector2f{ TILE_SIZE, TILE_SIZE };
	m_vertexes[3].position = m_position;
	m_vertexes[4].position = m_position + sf::Vector2f{ TILE_SIZE, TILE_SIZE };
	m_vertexes[5].position = m_position + sf::Vector2f{ 0.0f, TILE_SIZE};
}

void Player::updateTexCoords()
{
  	sf::Vector2f offset{};
	offset = m_texOffset + (sf::Vector2f{ TILE_SIZE * 3 * m_playerNo,0.0f } );
	//offset = m_texOffset + sf::Vector2f{64.0,0.0f };

	if (m_female)
	{
		offset += sf::Vector2f{ 0.0f, TILE_SIZE * 4 };
	}
	//m_animationFrame = 3;
	float left = TILE_SIZE * m_animationFrame;
	float right = TILE_SIZE * m_animationFrame + TILE_SIZE ;

	 //left = 32;
	 //right = 32+ TILE_SIZE;

	float top = static_cast<int>(m_facing) * TILE_SIZE;
	float bottom = static_cast<int>(m_facing) * TILE_SIZE + TILE_SIZE;

	m_vertexes[0].texCoords = offset + sf::Vector2f{ left,top };
	m_vertexes[1].texCoords = offset + sf::Vector2f{ right, top };
	m_vertexes[2].texCoords = offset + sf::Vector2f{ right, bottom};
	m_vertexes[3].texCoords = offset + sf::Vector2f{ left, top};
	m_vertexes[4].texCoords = offset + sf::Vector2f{ right, bottom };
	m_vertexes[5].texCoords = offset + sf::Vector2f{ left, bottom };
}

void Player::addFootStep()
{
	bool found{ false };
	m_noFootSteps = false;
	sf::Vector2f width{};
	sf::Vector2f height{};
	sf::Vector2f footPosition;
	int i{ 0 };
	while (i< MAX_FOOT_STEPS_6)
	{
		if (!found  && m_footSteps[i].color.a < 11) // fading by 1
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
			m_footSteps[i + 1].position = footPosition + width;
			m_footSteps[i + 1].color = FOOT_TOP;
			m_footSteps[i + 2].position = footPosition + width + height;
			m_footSteps[i + 2].color = FOOT_BOTTOM;
			m_footSteps[i + 3].position = footPosition;
			m_footSteps[i + 3].color = FOOT_TOP;
			m_footSteps[i + 4].position = footPosition + width + height;
			m_footSteps[i + 4].color = FOOT_BOTTOM;
			m_footSteps[i + 5].position = footPosition + height;
			m_footSteps[i + 5].color = FOOT_BOTTOM;
		}
		i += 6;
	}
}


