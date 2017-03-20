#ifndef PENGUIN
#define PENGUIN

#include "Enums.h"
#include "TextureManager.h"
#include <SFML\Graphics.hpp>








class Penguin
{
public:
	Penguin();
	~Penguin();
	bool move(Direction direction); // make the penguin move to the adjacent square no checking
	void update(sf::Time deltaTime);
	sf::VertexArray m_vertexes;	 // triangles used for sprite
	sf::VertexArray m_footSteps; // triangles used for steps
	bool m_alive; // penguin active
	bool m_ready; // penguin ready for another move
	sf::Vector2i m_square; // square on the gid the penguin is logically in, sprite catches up
	Direction m_facing; // which way he is facing / moving
	void position(); // set the sprite position for the current square (top left corner of square)
	void drown(); // start the penguim falling through ice sequence
	void fadeFootSteps(); // reduce the alpha of footspet particles
	void reset(); //reset the penguin after each level
private:
	bool m_drowning;  // when true penguin falls into ice and dies
	sf::Vector2f m_position; // position of top left of sprite
	int m_animationFrame; // current frame 0,1,2
	sf::Time m_perFrame; // time to display each frame
	sf::Time m_intraFrameDelay; // current amount of time this frame has been displayed for
	void updateVertexes(); // update vertex positions based on sprite position
	void updateTexCoords(); // update vertex tecture coords based on duirection and animation frame
	sf::Vector2f m_velocity; // displacement for sprite per update
	float m_step = TILE_SIZE / NO_PENGUIN_STEPS; // distance traveled per update
	sf::Vector2f m_texOffset; //offset into the texture atlas for penguim sprite sheet(sub)
	int m_stepstaken; // no of taken so far while moving one square
	void addFootStep(); // add a new particle left/right at current position
	void updateVertexesDrowning(); // update the vertex position for drowning effect
	
	bool m_leftFoot; // used to alternate foot prints
	int m_drownStep; // used for drowning animation
	bool m_noFootSteps; // used to determine when all step are invisible and no need to check alpha
};

#endif // !PENGUIN