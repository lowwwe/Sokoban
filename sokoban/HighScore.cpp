#include "HighScore.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <fstream>


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

	for (int i = 0; i < MAX_SCORES; i++)
	{
		m_scoresText[i].setFont(font);
		m_scoresText[i].setCharacterSize(24);
		m_scoresText[i].setColor(sf::Color::Blue);
		m_scoresText[i].setPosition(100.0f, 100.0f + i* 50.0f);
	}
}


HighScore::~HighScore()
{
}

void HighScore::update(sf::Time deltaTime)
{
	if (m_showOnly)
	{
		loadScores();
		m_showOnly = false;
	}
	if (s_newHighScore != sf::Time::Zero)
	{
		m_showOnly = false;
		m_newScore = s_newHighScore;
		s_newHighScore = sf::Time::Zero;
	}
}

void HighScore::render(sf::RenderWindow & window)
{
	window.clear(sf::Color{ 10,30,136,255 });
	
	for (int i = 0; i < MAX_SCORES; i++)
	{
		window.draw(m_scoresText[i]);
	}
	
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

void HighScore::loadScores()
{
	std::ifstream infile;
	std::string line;
	int i{ 0 };
	std::string time;
	infile.open("ASSETS\\IMAGES\\highscores.txt");
	while (!infile.eof() && i < MAX_SCORES)
	{
		infile >> line >> time;
		m_scoresText[i].setString(line + " " + time);
		i++;
	}
	infile.close();
}

void HighScore::saveScores()
{
}
