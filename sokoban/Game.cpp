#include "Game.h"
#include <SFML\Graphics.hpp>


int Game::screenWidth{ 600 };
int Game::screenHeight{ 600 };
GameState Game::currentState{ GameState::None };


Game::Game() : m_window(sf::VideoMode(Game::screenWidth, Game::screenHeight),"Pete's Sokoban")
{
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
		m_window.display();
		break;
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
