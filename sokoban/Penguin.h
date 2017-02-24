#ifndef PENGUIN
#define PENGUIN

#include "Enums.h"
#include <SFML\Graphics.hpp>

const int MAXPENGUIN = 5;
const int FRAMES = 3;
const int NO_STEPS = 50;
const int MAX_FOOT_STEPS_6 = 132;

const float TILE_SIZE{ 32.0f };





class Penguin
{
public:
	Penguin();
	~Penguin();
	bool move(Direction direction);
	void update(sf::Time deltaTime);
	sf::VertexArray m_vertexes;	
	sf::VertexArray m_footSteps;
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
	void addFootStep();
	bool m_leftFoot; // used to alternate foot prints
};

#endif // !PENGUIN