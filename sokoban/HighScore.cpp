#include "HighScore.h"
#include "Game.h"



sf::Time HighScore::s_newHighScore{ sf::Time::Zero };

HighScore::HighScore(sf::Font & font):
	m_font(font),
	m_showOnly{ true },
	m_newScore{sf::Time::Zero}
{
	m_promptText.setFont(font);
	m_promptText.setCharacterSize(24);
	m_promptText.setColor(sf::Color::Blue);
	m_promptText.setString("Press any Key to continue");
	sf::FloatRect textSize = m_promptText.getGlobalBounds();
	float xPosition = Game::screenWidth / 2 - textSize.width / 2;
	m_promptText.setPosition(xPosition, 560.0f);
}


HighScore::~HighScore()
{
}

void HighScore::update(sf::Time deltaTime)
{
}

void HighScore::render(sf::RenderWindow & window)
{
	window.clear(sf::Color{ 10,30,136,255 });
	window.draw(m_promptText);
}

void HighScore::processEvents(sf::Event & event)
{
	if (sf::Event::KeyPressed == event.type)
		if (sf::Keyboard::Key::BackSpace == event.key.code)
		{
			Game::currentState = GameState::MainMenu;
			m_showOnly = true;
			s_newHighScore = sf::Time::Zero;
			m_newScore = sf::Time::Zero;
		}
}
