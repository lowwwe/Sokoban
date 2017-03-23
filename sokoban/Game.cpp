#include "Game.h"
#include <SFML\Graphics.hpp>

#define TEST_FPS

int Game::screenWidth{ 600 }; 
int Game::screenHeight{ 600 };
GameState Game::currentState{ GameState::Licence };


Game::Game(sf::Font & font) : 
	m_window(sf::VideoMode(Game::screenWidth, Game::screenHeight),"Pete's Sokoban"),
	m_font(font),
	m_licence(font),
	m_splash(font),
	m_mainMenu(font),
	m_gamePlay(font),
	m_help(font),
	m_highScore(font),	
	m_credits(font)
{
	m_status.setFont(font);
	m_status.setCharacterSize(24);
	m_status.setColor(sf::Color::White);
	m_status.setPosition(100.0f, 300.0f);
	
#ifdef TEST_FPS
	updateFrameCount = 0;
	drawFrameCount = 0;
	secondTime = sf::Time::Zero;
	updateFps.setFont(m_font);
	updateFps.setPosition(120, 560);
	updateFps.setCharacterSize(12);
	updateFps.setColor(sf::Color::White);
	drawFps.setFont(m_font);
	drawFps.setPosition(20, 560);
	drawFps.setCharacterSize(12);
	drawFps.setColor(sf::Color::White);
#endif // TEST_FPS
}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;

			processEvents();
			update(timePerFrame);
#ifdef TEST_FPS
			secondTime += timePerFrame;
			updateFrameCount++;
			if (secondTime.asSeconds() > 1)
			{
				char bufferDps[256];
				char bufferUps[256];
				sprintf_s(bufferUps, "%d UPS", updateFrameCount - 1);
				updateFps.setString(bufferUps);
				sprintf_s(bufferDps, "%d DPS", drawFrameCount);
				drawFps.setString(bufferDps);
				updateFrameCount = 0;
				drawFrameCount = 0;
				secondTime = sf::Time::Zero;
			}
#endif // TEST_FPS
		}
		render();
#ifdef TEST_FPS
		drawFrameCount++;
#endif // TEST_FPS
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		switch (currentState)
		{
		case GameState::Licence:
			break;
		case GameState::Splash:
			m_splash.processEvents(event);
			break;
		case GameState::MainMenu:
			m_mainMenu.processEvents(event);
			break;
		case GameState::Help:
			m_help.processEvents(event);
			break;
		case GameState::Game:
			m_gamePlay.processEvents(event);
			break;
		case GameState::Credits:
			m_credits.processEvents(event);
			break;
		case GameState::HighScore:
			m_highScore.processEvents(event);
			break;
		case GameState::Exit:
			m_window.close();
			break;
		default:
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	switch (currentState)
	{
	case GameState::None:
		break;
	case GameState::Licence:
		m_licence.update(deltaTime);
		break;
	case GameState::Splash:
		m_splash.update(deltaTime);
		break;
	case GameState::MainMenu:
		m_mainMenu.update(deltaTime);
		break;
	case GameState::Help:
		m_help.update(deltaTime);
		break;
	case GameState::Game:
		m_gamePlay.update(deltaTime);
		break;
	case GameState::Credits:
		m_credits.update(deltaTime);
		break;
	case GameState::HighScore:
		m_highScore.update(deltaTime);
		break;
	case GameState::Exit:

		break;
	default:
		break;
	}
}

void Game::render()
{
	switch (currentState)
	{
	case GameState::None:
		m_window.clear(sf::Color::Red);
		m_status.setString("Game State None");
		m_window.draw(m_status);
		
		break;
	case GameState::Licence:
		m_licence.render(m_window);
		break;
	case GameState::Splash:
		m_splash.render(m_window);
		break;
	case GameState::MainMenu:
		m_mainMenu.render(m_window);
		break;
	case GameState::Help:
		m_help.render(m_window);		
		break;
	case GameState::Game:
		m_gamePlay.render(m_window);
		break;
	case GameState::HighScore:
		m_highScore.render(m_window);
		break;
	case GameState::Credits:
		m_credits.render(m_window);		
		break;
	case GameState::Exit:
		m_window.clear(sf::Color::Red);
		m_status.setString("Game State Exit");
		m_window.draw(m_status);
		
		break;
	default:
		break;
	}
#ifdef TEST_FPS
	m_window.draw(updateFps);
	m_window.draw(drawFps);
#endif // TEST_FPS
	m_window.display();
}
