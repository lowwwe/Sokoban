#ifndef PENGUIN
#define PENGUIN


#include <SFML\Graphics.hpp>

#define MAXPENGUIN 5
#define FRAMES 3
#define NO_STEPS 50

const float TILE_SIZE{ 32.0f };

enum class
	Direction
{
	Down =0,
	Left =1,
	Right =2,
	Up = 3
};

class Penguin
{
public:
	Penguin();
	~Penguin();
	bool move(Direction direction);
	void update(sf::Time deltaTime);
	sf::VertexArray m_vertexes;	
	bool m_alive;
	bool m_ready;
	sf::Vector2i m_square;
	Direction m_facing;
	void position();
private:
	sf::Vector2f m_position;
	int m_animationFrame;
	sf::Time m_perFrame;
	sf::Time m_intraFrameDelay;
	void updateVertexes();
	void updateTexCoords();
	sf::Vector2f m_velocity;
	float m_step = 32.0f / NO_STEPS;
	sf::Vector2f m_texOffset;
	int m_stepstaken;
	
};

#endif // !PENGUIN