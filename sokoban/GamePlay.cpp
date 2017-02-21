#include "GamePlay.h"
#include <iostream>
#include <string>
#include <fstream>



GamePlay::GamePlay(sf::Font & font):
	m_font{ font },
	m_base{sf::Triangles}
{
	m_textureCoOrds = TextureManager::getRect("tiles");
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
	window.clear(sf::Color::Black);
	window.draw(m_base, &TextureManager::texture);
	window.display();
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
	sf::Vector2f offset{ m_textureCoOrds.left, m_textureCoOrds.top };
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
					vertex.texCoords = sf::Vector2f{(m_baseLevel[row][col]/4)*TILE_SIZE,(m_baseLevel[row][col] % 4)*TILE_SIZE } +offset;
					break;
				case 1:
					vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE } +TOP_LEFT;
					vertex.texCoords = sf::Vector2f{ (m_baseLevel[row][col] / 4)*TILE_SIZE + +TILE_SIZE,(m_baseLevel[row][col] % 4)*TILE_SIZE } +offset;
					break;
				case 2:
					vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE + TILE_SIZE } +TOP_LEFT;
					vertex.texCoords = sf::Vector2f{ (m_baseLevel[row][col] / 4)*TILE_SIZE + +TILE_SIZE,(m_baseLevel[row][col] % 4)*TILE_SIZE + TILE_SIZE } +offset;
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
