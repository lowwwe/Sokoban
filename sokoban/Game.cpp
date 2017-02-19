#include "Game.h"
#include <SFML\Graphics.hpp>


int Game::screenWidth{ 600 }; 
int Game::screenHeight{ 600 };
GameState Game::currentState{ GameState::Licence };


Game::Game(sf::Font & font) : 
	m_window(sf::VideoMode(Game::screenWidth, Game::screenHeight),"Pete's Sokoban"),
	m_font(font),
	m_licence(font)

{
	m_status.setFont(font);
	m_status.setCharacterSize(24);
	m_status.setColor(sf::Color::White);
	m_status.setPosition(100.0f, 300.0f);
	
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
		}
		render();
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
		
			break;
		case GameState::MainMenu:
			break;
		case GameState::Help:
		
			break;
		case GameState::Game:
		
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
		break;
	case GameState::MainMenu:
		break;
	case GameState::Help:
		break;
	case GameState::Game:
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
		m_window.display();
		break;
	case GameState::Licence:
		m_licence.render(m_window);
		break;
	case GameState::Splash:
		m_window.clear(sf::Color::Red);
		m_status.setString("Game State Splash");
		m_window.draw(m_status);
		m_window.display();
		break;
	case GameState::MainMenu:
		m_window.clear(sf::Color::Red);
		m_status.setString("Game State Main Menu");
		m_window.draw(m_status);
		m_window.display();
		break;
	case GameState::Help:
		m_window.clear(sf::Color::Red);
		m_status.setString("Game State Help");
		m_window.draw(m_status);
		m_window.display();
		break;
	case GameState::Game:
		m_window.clear(sf::Color::Red);
		m_status.setString("Game State Game");
		m_window.draw(m_status);
		m_window.display();
		break;
	default:
		break;
	}

}
