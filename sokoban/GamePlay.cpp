#include "GamePlay.h"
#include <iostream>
#include <string>
#include <fstream>



GamePlay::GamePlay(sf::Font & font):
	m_font{ font },
	m_base{sf::Triangles},
	m_penguinVertexes{sf::Triangles},
	m_penguins{}

{
	m_textureCoOrds = TextureManager::getRect("tiles");
	setupLevel();
}


GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time deltaTime)
{
	for (size_t i = 0; i < MAXPENGUIN; i++)
	{
		m_penguins[i].update(deltaTime);
	}
	addPenguinVertexes();
	if (m_penguins[0].m_ready)
	{
		if (m_baseLevel[m_penguins[0].m_square.x+1][m_penguins[0].m_square.y] == 5)
		{
			m_penguins[0].move(Direction::Down);
		}
	}
}

void GamePlay::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	window.draw(m_base, &TextureManager::texture);
	window.draw(m_penguinVertexes, &TextureManager::texture);
	window.display();
}

void GamePlay::processEvents(sf::Event & event)
{
}

void GamePlay::setupLevel()
{
	
	loadBaseFile();	
	setupBaseVertexes();
	loadItemsFile();
	setupItemsVertexes();
	
	
}

void GamePlay::addPenguinVertexes()
{
	m_penguinVertexes.clear();
	for (size_t i = 0; i < MAXPENGUIN; i++)
	{
		for (size_t j = 0; j < 6; j++)
		{
			m_penguinVertexes.append(m_penguins[i].m_vertexes[j]);
		}		
	}
}
void GamePlay::loadBaseFile()
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

void GamePlay::setupBaseVertexes()
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
				case 3:
					vertex.position = sf::Vector2f{ col * TILE_SIZE,row * TILE_SIZE } +TOP_LEFT;
					vertex.texCoords = sf::Vector2f{ (m_baseLevel[row][col] % GRIDSIZE)*TILE_SIZE,(m_baseLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
					break;
				case 1:
					vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE } +TOP_LEFT;
					vertex.texCoords = sf::Vector2f{ (m_baseLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(m_baseLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
					break;
				case 2:
				case 4:
					vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE + TILE_SIZE } +TOP_LEFT;
					vertex.texCoords = sf::Vector2f{ (m_baseLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(m_baseLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
					break;
				case 5:
					vertex.position = sf::Vector2f{ col * TILE_SIZE, row * TILE_SIZE + TILE_SIZE } +TOP_LEFT;
					vertex.texCoords = sf::Vector2f{ (m_baseLevel[row][col] % GRIDSIZE)*TILE_SIZE ,(m_baseLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
					break;
				}
				m_base.append(vertex);
			}
		}
	}
}

void GamePlay::loadItemsFile()
{
	std::ifstream infile;
	std::string name;
	std::string equals;
	sf::IntRect coords;
	int i{ 0 };
	infile.open("ASSETS\\IMAGES\\items1.txt");
	while (!infile.eof() && i < TILES_HIGH)
	{
		infile >> m_itemsLevel[i][0] >> m_itemsLevel[i][1] >> m_itemsLevel[i][2] >> m_itemsLevel[i][3]
			>> m_itemsLevel[i][4] >> m_itemsLevel[i][5] >> m_itemsLevel[i][6] >> m_itemsLevel[i][7]
			>> m_itemsLevel[i][8] >> m_itemsLevel[i][9] >> m_itemsLevel[i][10] >> m_itemsLevel[i][11]
			>> m_itemsLevel[i][12] >> m_itemsLevel[i][13] >> m_itemsLevel[i][14] >> m_itemsLevel[i][15];
		i++;
	}
	infile.close();
}

void GamePlay::setupItemsVertexes()
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
				case 3:
					vertex.position = sf::Vector2f{ col * TILE_SIZE,row * TILE_SIZE} + TOP_LEFT;
					vertex.texCoords = sf::Vector2f{(m_itemsLevel[row][col]% GRIDSIZE)*TILE_SIZE,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
					break;
				case 1:
					vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE } +TOP_LEFT;
					vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE  + TILE_SIZE,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
					break;
				case 2:
				case 4:
					vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE + TILE_SIZE } +TOP_LEFT;
					vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE  +TILE_SIZE,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
					break;
				case 5:
					vertex.position = sf::Vector2f{ col * TILE_SIZE, row * TILE_SIZE + TILE_SIZE } +TOP_LEFT;
					vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE ,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
					break;
				}				
				m_base.append(vertex);
			}
		}
	}
}


