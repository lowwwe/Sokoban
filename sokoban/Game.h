#ifndef GAME
#define GAME

#include <SFML\Graphics.hpp>
#include "Licence.h"
#include "Splash.h"
#include "GamePlay.h"
#include "MainMenu.h"
#include "Enums.h"


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
	GamePlay m_gamePlay;

	sf::Text updateFps;
	sf::Text drawFps;
	int updateFrameCount;
	int drawFrameCount;
	sf::Time secondTime;

	sf::RenderWindow m_window;
	sf::Font m_font; // used everywhere
	sf::Text m_status; // used for status errors and new states
};

#endif // !GAME