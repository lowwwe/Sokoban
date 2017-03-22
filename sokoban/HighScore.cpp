#include "HighScore.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <fstream>


sf::Time HighScore::s_newHighScore{ sf::Time::Zero };

HighScore::HighScore(sf::Font & font):
	m_font(font),
	m_showOnly{ true },
	m_newScore{sf::Time::Zero},
	m_addScore{ false },
	m_iBar{sf::Lines},
	m_iBarCount{ 0 },
	m_showIBar{false},
	m_newName{"Anon"}
{
	m_promptText.setFont(font);
	m_promptText.setCharacterSize(24);
	m_promptText.setColor(sf::Color::Blue);
	m_promptText.setString("Enter your name");
	sf::FloatRect textSize = m_promptText.getGlobalBounds();
	float xPosition = Game::screenWidth / 2 - textSize.width / 2;
	m_promptText.setPosition(xPosition, 360.0f);
	m_inputBox.setFillColor(sf::Color::White);
	m_inputBox.setOutlineColor(sf::Color::Black);
	m_inputBox.setOutlineThickness(3.0f);
	m_inputBox.setPosition(200.0f, 400.0f);
	m_inputBox.setSize({ 200.0f, 60.0f });
	m_nameInput.setFont(font);
	m_nameInput.setCharacterSize(24);
	m_nameInput.setColor(sf::Color::Blue);
	m_nameInput.setPosition(210.0f, 410.0f);


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
	const int BLINK_TIME{ 30 };
	
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
		m_addScore = true;
	}
	if (m_addScore)
	{
		if (m_iBarCount < BLINK_TIME)
		{
			m_iBarCount++;			
		}		
		else
		{
			m_iBarCount = 0;
			m_showIBar = !m_showIBar;
		}
	}
}

void HighScore::render(sf::RenderWindow & window)
{
	window.clear(sf::Color{ 10,30,136,255 });
	if (m_addScore)
	{
		window.draw(m_promptText);
		window.draw(m_inputBox);
		window.draw(m_nameInput);
		if (m_showIBar)
		{
			window.draw(m_iBar);
		}
	}
	for (int i = 0; i < MAX_SCORES; i++)
	{
		window.draw(m_scoresText[i]);
	}
	
}

void HighScore::processEvents(sf::Event & event)
{
	
	if (event.type == sf::Event::TextEntered && m_addScore)
	{

		if (event.text.unicode < 128)
		{
			if (event.text.unicode == '\b')
			{
				if (m_newName.length() > 0)
				{
					m_newName.pop_back();
				}
			}
			if (event.text.unicode == 13)
			{
				addName();
			}

			if(event.text.unicode > 32)
			{
				m_newName += static_cast<char>(event.text.unicode);
			}
		}
		m_nameInput.setString(m_newName);
	}
	if (sf::Event::KeyPressed == event.type)
	{
		if (sf::Keyboard::Key::Escape == event.key.code)
		{
			Game::currentState = GameState::MainMenu;
			m_showOnly = true;
			s_newHighScore = sf::Time::Zero;
			m_newScore = sf::Time::Zero;
		}

	}
}

void HighScore::loadScores()
{
	std::ifstream infile;
	std::string line;
	int i{ 0 };
	double hundreds{ 0 };
	std::string time;
	infile.open("ASSETS\\IMAGES\\highscores.txt");
	if (infile.is_open())
	{
		while (!infile.eof() && i < MAX_SCORES)
		{
			infile >> line >> time >> hundreds;
			m_scoresText[i].setString(line + " " + time );
			m_scoreValue[i] = hundreds;
			i++;
		}
		infile.close();
	}
}

void HighScore::saveScores()
{
	std::ofstream outfile;
	std::string line;
	outfile.open("ASSETS\\IMAGES\\highscores.txt", std::ofstream::trunc);
	if (outfile.is_open())
	{
		for (int i = 0; i < MAX_SCORES; i++)
		{
			line = m_scoresText[i].getString();
			outfile << line << " " << m_scoreValue[i] << std::endl;
		}
		outfile.close();
	}
}

void HighScore::addName()
{
	std::string time{};
	int min = static_cast<int>(m_newScore.asSeconds()) / 60;
	int seconds = static_cast<int>(m_newScore.asSeconds()) % 60;
	int hundreds = static_cast<int>((m_newScore.asSeconds() * 100.0f) - (seconds * 100.0f));

	if (min >0)
	{
		time = std::to_string(min) + ":";
		if (seconds < 10)
		{
			time += "0";
		}
		if (seconds == 0)
		{
			time += "0";
		}
	}
	time += std::to_string(seconds);	
	time += "." + std::to_string(hundreds);	
	m_showOnly = true;
	m_addScore = false;
	int i = MAX_SCORES - 1;
	if (m_newScore.asMilliseconds() < m_scoreValue[i])
	{		
		while (i > 0 && m_newScore.asMilliseconds() < m_scoreValue[i])
		{
			m_scoresText[i].setString(m_scoresText[i - 1].getString());
			m_scoreValue[i] = m_scoreValue[i - 1];
			i--;
		}
		m_scoresText[i].setString(m_newName + " " + time);
		m_scoreValue[i] = m_newScore.asMilliseconds();
		saveScores();
	}
}
