#include "Splash.h"
#include "Game.h"
#include "TextureManager.h"
#include <iostream>


Splash::Splash(sf::Font & font) :
	m_font(font),
	m_background(sf::Triangles),
	m_keypressed {false}
{
	sf::FloatRect CoOrds = TextureManager::getRect("splash");

	
	m_promptText.setFont(font);
	m_promptText.setCharacterSize(24);
	m_promptText.setFillColor(sf::Color::Blue);
	m_promptText.setString("Press any Key to continue");
	sf::FloatRect textSize = m_promptText.getGlobalBounds();
	float xPosition = Game::screenWidth / 2 - textSize.width / 2;
	m_promptText.setPosition(xPosition, 560.0f);

	m_background.append(sf::Vertex{ sf::Vector2f{0,0},sf::Vector2f{ CoOrds.left,CoOrds.top} }); // topleft
	m_background.append(sf::Vertex{ sf::Vector2f{ 600,0 },sf::Vector2f{ CoOrds.left + CoOrds.width,CoOrds.top } }); //top right
	m_background.append(sf::Vertex{ sf::Vector2f{ 600,600 },sf::Vector2f{ CoOrds.left + CoOrds.width,CoOrds.top + CoOrds.height } }); // bottom right

	m_background.append(sf::Vertex{ sf::Vector2f{ 0,0 },sf::Vector2f{ CoOrds.left,CoOrds.top } }); //top left
	m_background.append(sf::Vertex{ sf::Vector2f{ 600,600 },sf::Vector2f{ CoOrds.left + CoOrds.width,CoOrds.top + CoOrds.height } }); // bottom right
	m_background.append(sf::Vertex{ sf::Vector2f{ 0,600 },sf::Vector2f{ CoOrds.left,CoOrds.top + CoOrds.height } }); // bottom left

	
}


Splash::~Splash()
{
}

void Splash::update(sf::Time deltaTime)
{
	if (m_keypressed)
	{
		Game::currentState = GameState::MainMenu;
	}
}

void Splash::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	window.draw(m_background, &TextureManager::texture);
	window.draw(m_promptText);	
}

void Splash::processEvents(sf::Event & event)
{
	if (sf::Event::KeyPressed == event.type)
	{	
			m_keypressed = true;	
	}
}
