#include "Help.h"
#include "Game.h"






Help::Help(sf::Font & font):
	m_font{ font }
{
	m_helpText.setFont(font);
	m_helpText.setCharacterSize(24);
	m_helpText.setFillColor(sf::Color::White);
	m_helpText.setString("Use arrow keys to move \nLeft <shift> to push a barrel\nLeft <ALt> to shove a barrel\nGet to the exit when all the\npenguins are dead in the\nshortest time\n\n<Escape> to return to menu");
	sf::FloatRect textSize = m_helpText.getGlobalBounds();
	float xPosition = Game::screenWidth / 2 - textSize.width / 2;
	m_helpText.setPosition(xPosition, 120.0f);
}

Help::~Help()
{
}

void Help::update(sf::Time deltaTime)
{
}

void Help::render(sf::RenderWindow & window)
{
	window.clear(sf::Color{ 10,30,136,255 });
	window.draw(m_helpText);
}

void Help::processEvents(sf::Event & event)
{
	if (sf::Event::KeyPressed == event.type)
		if(	sf::Keyboard::Key::Escape == event.key.code)
	{
		Game::currentState = GameState::MainMenu;
	}
}
