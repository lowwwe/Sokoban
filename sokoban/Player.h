#ifndef PLAYER
#define PLAYER


#include <SFML\Graphics.hpp>
#include "Enums.h"
#include "Colours.h"
#include "TextureManager.h"

class Player
{
public:
	Player();
	~Player();
	int m_playerNo; // index into player sprite sheet
	sf::VertexArray m_vertexes;	 // triangles used for sprite
	sf::VertexArray m_footSteps; // triangles used for steps
	bool move(Direction direction); // make the player move to the adjacent square no checking
	void update(sf::Time deltaTime);
	sf::Vector2i m_square; // square on the gid the player is logically in, sprite catches up
	Direction m_facing; // which way he is facing / moving
	void position(); // set the sprite position for the current square (top left corner of square)
	bool m_ready; // Player ready for another move
	void fadeFootSteps(); // reduce the alpha of footspet particles

private:
	sf::Vector2f m_texOffset; //offset into the texture atlas for characters
	sf::Vector2f m_position; // position of top left of sprite
	int m_animationFrame; // current frame 0,1,2
	sf::Time m_perFrame; // time to display each frame
	sf::Time m_intraFrameDelay; // current amount of time this frame has been displayed for
	int m_stepstaken; // no of taken so far while moving one square
	bool m_leftFoot; // used to alternate foot prints	
	bool m_noFootSteps; // used to determine when all step are invisible and no need to check alpha
	void updateVertexes(); // update vertex positions based on sprite position
	void updateTexCoords(); // update vertex tecture coords based on character, direction and animation frame
	bool m_female; // is the character female
	void addFootStep(); // add a new particle left/right at current position
	sf::Vector2f m_velocity; // displacement for sprite per update
	float m_step = TILE_SIZE / NO_PLAYER_STEPS; // distance traveled per update
};

#endif // !PLAYER