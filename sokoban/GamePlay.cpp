#include "GamePlay.h"
#include <iostream>
#include <string>
#include <fstream>



GamePlay::GamePlay(sf::Font & font):
	m_font{ font }
{
	setupLevel();
}


GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time deltaTime)
{
}

void GamePlay::render(sf::RenderWindow & window)
{
}

void GamePlay::processEvents(sf::Event & event)
{
}

void GamePlay::setupLevel()
{
	loadFile();	
	setupVertexes();
	
}

void GamePlay::loadFile()
{
	std::ifstream infile;
	std::string name;
	std::string equals;
	sf::IntRect coords;
	int i{ 0 };
	infile.open("ASSETS\\IMAGES\\level1.txt");
	while (!infile.eof() && i < TILES_HIGH)
	{
		infile >> m_baseLevel[i][0] >> m_baseLevel[i][1] >> m_baseLevel[i][2] >> m_baseLevel[i][3]
			>> m_baseLevel[i][4] >> m_baseLevel[i][5] >> m_baseLevel[i][6] >> m_baseLevel[i][7]
			>> m_baseLevel[i][8] >> m_baseLevel[i][9] >> m_baseLevel[i][10] >> m_baseLevel[i][11]
			>> m_baseLevel[i][12] >> m_baseLevel[i][13] >> m_baseLevel[i][14] >> m_baseLevel[i][15];
		i++;
	}
	infile.close();
}

void GamePlay::setupVertexes()
{
	for (int row = 0; row < TILES_HIGH; row++)
	{
		for (int col = 0; col < TILES_WIDE; col++)
		{
			for (int i = 0; i < 6; i++)
			{
				sf::Vertex vertex;
				switch (i)
				{
				case 0:
					vertex.position = sf::Vector2f{ col * TILE_SIZE,row * TILE_SIZE} + TOP_LEFT;
					vertex.texCoords = sf::Vector2f{};
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				}				
				m_base.append(vertex);
			}
		}
	}
}
