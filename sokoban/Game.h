#ifndef GAME
#define GAME

#include <SFML\Graphics.hpp>

enum class
	GameState
{
	None,
	Licence,
	Splash,
	MainMenu,
	Help,
	Game
};

class Game
{
public:
	Game();
	~Game();
	void run();

	static int screenWidth;
	/// screen width in pixels
	static int screenHeight;
	/// current game state
	static GameState currentState;
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	sf::RenderWindow m_window;
};

#endif // !GAME