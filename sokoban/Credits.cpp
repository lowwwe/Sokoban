#include "Credits.h"
#include "Game.h"
#include <iostream>

Credits::Credits( sf::Font font) :
	
	m_comicSans{ font },
	m_creditLines{},
	m_offset{ true },
	
	m_exitSpeed{ 15 },
	m_blankLine{ true },
	m_offsetStep{1.0f}
{
	
	m_artistsFile.open("ASSETS\\DATA\\credits.txt");
	if (!m_artistsFile.eof())
	{
		m_fileOpen = true;
		int i = 0;
		while (!m_artistsFile.eof() && i < MAX_LINES)
		{
			readNextLine(i, 500 + i * 30);
			i++;
		}		
	}
	if (m_artistsFile.eof())
	{
		m_fileOpen = false;
		m_artistsFile.close();
	}
	m_translation = sf::Transform::Identity;
}

bool Credits::readNextLine(int index, int maxOffset)
{
	std::string fileLine;
	m_creditLines[index].setFont(m_comicSans);
	m_creditLines[index].setColor(sf::Color::White);
	if (m_blankLine)
	{
		m_creditLines[index].setCharacterSize(25);
		m_blankLine = false;
	}
	else
	{
		m_creditLines[index].setCharacterSize(20);
	}
	m_creditLines[index].setPosition(-100, -100);
	std::getline(m_artistsFile, fileLine);
	if (fileLine == "")
	{
		m_blankLine = true;
	}
	m_creditLines[index].setPosition(100.0f, static_cast<float>( maxOffset));
	m_creditLines[index].setString(fileLine);
	m_creditLines[index].m_active = true;
	if (m_artistsFile.eof())
	{
		m_fileOpen = false;
		m_artistsFile.close();
	}
	return false;
}

Credits::~Credits()
{
	std::cout << "destructing Credits" << std::endl;
}

void Credits::update(sf::Time deltaTime)
{
	sf::Vector2f position{};
	float maxDisplacement{ 0.0f };
	m_cumulativeTime += deltaTime;
	bool allFinished = true;	
	for (int i = 0; i < MAX_LINES; i++)
	{
		if (m_creditLines[i].m_active)
		{
			allFinished = false;
			position = m_creditLines[i].getPosition();
			m_offsetStep += 0.0001f;
			position.y -= m_offsetStep;
			m_creditLines[i].setPosition(position);
		}		
		if (position.y < -30)
		{
			m_creditLines[i].m_active = false;
			if (m_fileOpen)
			{
				for (int j = 0; j < MAX_LINES; j++)
				{
					if (m_creditLines[j].getPosition().y > maxDisplacement)
					{
						maxDisplacement = m_creditLines[j].getPosition().y;
					}
				}
				readNextLine(i, maxDisplacement + 30.0f);
			}

		}
	}
	if (allFinished)
	{
		Game::currentState = GameState::MainMenu;
	}
}

void Credits::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	for (int i = 0; i < MAX_LINES; i++)
	{
		if (m_creditLines[i].m_active)
		{
			window.draw(m_creditLines[i]);
		}
	}	
}

void Credits::processEvents(sf::Event & event)
{
}


