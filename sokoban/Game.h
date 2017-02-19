#ifndef GAME
#define GAME

#include <SFML\Graphics.hpp>
#include "Licence.h"
#include "Splash.h"
#include "TextureManager.h"
#include "MainMenu.h"

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
	Game(sf::Font & font);
	~Game();
	void run();

	static int screenWidth;
	/// screen width & Height in pixels
	static int screenHeight;
	/// current game state
	static GameState currentState;
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	
	Licence m_licence;
	Splash m_splash;
	MainMenu m_mainMenu;
	


	sf::RenderWindow m_window;
	sf::Font m_font; // used everywhere
	sf::Text m_status; // used for status errors and new states
};

#endif // !GAME