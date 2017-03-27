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
	m_iBar{sf::Lines,4U},
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
	m_promptText.setPosition(xPosition, INPUT_OFFSET.y + 70.0f);
	m_inputBox.setFillColor(sf::Color::White);
	m_inputBox.setOutlineColor(sf::Color::Black);
	m_inputBox.setOutlineThickness(3.0f);
	m_inputBox.setPosition(INPUT_OFFSET);
	m_inputBox.setSize({ 300.0f, 50.0f });
	m_nameInput.setFont(font);
	m_nameInput.setCharacterSize(24u);
	m_nameInput.setColor(sf::Color::Blue);
	m_nameInput.setPosition(INPUT_OFFSET + sf::Vector2f{ 10.0f, 10.0f });
	m_nameInput.setString(m_newName);
	m_iBar[0].color = sf::Color::Blue;
	m_iBar[1].color = sf::Color::Blue;
	m_iBar[2].color = sf::Color::Blue;
	m_iBar[3].color = sf::Color::Blue;
	m_iBar[0].position = INPUT_OFFSET + sf::Vector2f{10.0f,10.0f} ;
	m_iBar[1].position = INPUT_OFFSET + sf::Vector2f{ 10.0f,40.0f } ;
	m_iBar[2].position = INPUT_OFFSET + sf::Vector2f{ 11.0f,10.0f };
	m_iBar[3].position = INPUT_OFFSET + sf::Vector2f{ 11.0f,40.0f };
	for (int i = 0; i < MAX_SCORES; i++)
	{
		m_scoresText[i].setFont(font);
		m_scoresText[i].setCharacterSize(24);
		m_scoresText[i].setColor(sf::Color::Blue);
		m_scoresText[i].setPosition(150.0f, 40.0f + i* 40.0f);
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
	for (int i = 0; i < MAX_SCORES; i++)
	{
		window.draw(m_scoresText[i]);
	}
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

			if(event.text.unicode > 31 && m_newName.length() < MAX_LETTERS)
			{
				m_newName += static_cast<char>(event.text.unicode);
			}
		}
		m_nameInput.setString(m_newName);
		
		sf::FloatRect textBounds = m_nameInput.getGlobalBounds();
		m_iBar[0].position = sf::Vector2f{ textBounds.left + textBounds.width + 2.0f, textBounds.top -1.0f };
		m_iBar[1].position = sf::Vector2f{ textBounds.left + textBounds.width + 2.0f, textBounds.top + textBounds.height + 1.0f};
		m_iBar[2].position = sf::Vector2f{ textBounds.left + textBounds.width + 3.0f, textBounds.top -1.0f };
		m_iBar[3].position = sf::Vector2f{ textBounds.left + textBounds.width + 3.0f, textBounds.top  + textBounds.height + 1.0f };
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
	infile.open("ASSETS\\DATA\\highscores.txt");
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
	outfile.open("ASSETS\\DATA\\highscores.txt", std::ofstream::trunc);
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
