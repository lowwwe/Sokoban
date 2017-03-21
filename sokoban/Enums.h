#ifndef ENUMS
#define ENUMS

const int MAX_FOOT_STEPS_6 = 132;// number of vertexes for footsteps divide by six
const int MAX_PENGUIN = 2; // No of penguins in game
const int FRAMES = 3; // No frames for each direction
const int NO_PENGUIN_STEPS = 50; // number of frames to move one square
const int NO_PLAYER_STEPS = 30; // number of frames to move one square
						 

enum class
	Direction
{
	Down = 0,
	Left = 1,
	Right = 2,
	Up = 3,
	None = 4
};

enum class
	GameState
{
	None,
	Licence,
	Splash,
	MainMenu,
	Help,
	Game,
	Exit,
	Credits,
	HighScore
};








#endif // !ENUMS

