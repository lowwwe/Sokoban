#include "Licence.h"
#include "Game.h"



Licence::Licence(sf::Font & font) :
	m_font{ font }
{
	m_licenceText.setFont(font);
	m_licenceText.setCharacterSize(24);
	m_licenceText.setColor(sf::Color::White);
	m_licenceText.setString("Hand Made by Pete");
	sf::FloatRect textSize = m_licenceText.getGlobalBounds();
	float xPosition = Game::screenWidth / 2 - textSize.width / 2;
	m_licenceText.setPosition(xPosition, 120.0f);	
	m_delay = sf::seconds(0);
}


Licence::~Licence()
{
}

void Licence::update(sf::Time deltaTime)
{
	m_delay += deltaTime;
	if (m_delay.asSeconds() > 1.0f)
	{
		Game::currentState = GameState::Splash;
	}
}

void Licence::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	window.draw(m_licenceText);
	
}
