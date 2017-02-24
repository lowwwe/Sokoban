#include "GamePlay.h"
#include <iostream>
#include <string>
#include <fstream>




GamePlay::GamePlay(sf::Font & font):
	m_font{ font },
	m_background{sf::Triangles},
	m_foreground{sf::Triangles},
	m_penguinVertexes{sf::Triangles},
	m_penguins{ {} }

{
	m_textureCoOrds = TextureManager::getRect("tiles");
	setupLevel();
}


GamePlay::~GamePlay()
{
}

void GamePlay::update(sf::Time deltaTime)
{
	m_penguinVertexes.clear();
	for (size_t i = 0; i < MAX_PENGUIN; i++)
	{
		bool moved{ false };
		m_penguins[i].fadeFootSteps();
		if (m_penguins[i].m_alive)
		{
			m_penguins[i].update(deltaTime);
			addPenguinVertexes(i);
			if (m_penguins[i].m_ready)
			{
				int row = m_penguins[i].m_square.x;
				int col = m_penguins[i].m_square.y;
				if (m_itemsLevel[row][col] == ICE_POOL)
				{
					m_penguins[i].drown();
					moved = true; // ensure penguin doenst move
				}				
				while (!moved)
				{
					switch (m_penguins[i].m_facing)
					{
					case Direction::Down:
						if (m_navigation[row + 1][col])
						{
							std::cout << "down x" << m_penguins[i].m_square.x << ", y " << m_penguins[i].m_square.y << std::endl;
							m_penguins[i].move(Direction::Down);
							moved = true;
						}
						else
						{
							m_penguins[i].m_facing = newDirection(Direction::Left);
						}
						break;
					case Direction::Left:
						if (m_navigation[row][col - 1])
						{
							std::cout << "Left x" << m_penguins[i].m_square.x << ", y " << m_penguins[i].m_square.y << std::endl;
							m_penguins[i].move(Direction::Left);
							moved = true;
						}
						else
						{
							m_penguins[i].m_facing = newDirection(Direction::Up);
						}
						break;
					case Direction::Right:
						if (m_navigation[row][col + 1])
						{
							std::cout << "Right x" << m_penguins[i].m_square.x << ", y " << m_penguins[i].m_square.y << std::endl;
							m_penguins[i].move(Direction::Right);
							moved = true;
						}
						else
						{
							m_penguins[i].m_facing = newDirection(Direction::Down);
						}
						break;
					case Direction::Up:
						if (m_navigation[row - 1][col])
						{
							std::cout << "UP x" << m_penguins[i].m_square.x << ", y " << m_penguins[i].m_square.y << std::endl;
							m_penguins[i].move(Direction::Up);
							moved = true;
						}
						else
						{
							m_penguins[i].m_facing = newDirection(Direction::Right);
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

void GamePlay::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	window.draw(m_background, &m_newTexture.getTexture());	
	for (int i = 0; i < MAX_PENGUIN; i++)
	{
		window.draw(m_penguins[i].m_footSteps);
	}	
	window.draw(m_penguinVertexes, &m_newTexture.getTexture());
	window.draw(m_foreground, &m_newTexture.getTexture());
	
}

void GamePlay::processEvents(sf::Event & event)
{
}

void GamePlay::setupLevel()
{
	
	setupTexture();
	loadItemsFile();
	setupItemsVertexes();
	setupNavigation();
	for (int i = 0; i < MAX_PENGUIN; i++)
	{
		while (!m_navigation[m_penguins[i].m_square.x][m_penguins[i].m_square.x])
		{
			m_penguins[i].m_square.x = std::rand() % 16;
			m_penguins[i].m_square.y = std::rand() % 16;
		}
		m_penguins[i].position();
	}
	
}

void GamePlay::addPenguinVertexes(int index)
{	
	for (size_t j = 0; j < 6; j++)
	{
		m_penguinVertexes.append(m_penguins[index].m_vertexes[j]);
	}
}
void GamePlay::setupNavigation()
{
	for (int row = 0; row < TILES_HIGH; row++)
	{
		for (int col = 0; col < TILES_WIDE; col++)
		{
			m_navigation[row][col] = true;
			switch (m_baseLevel[row][col])
			{
			case 1:
			case 6:
			case 7:
				m_navigation[row][col] = false;
				break;			
			}
			switch (m_itemsLevel[row][col])
			{
			case 2:
			case 3:
			case 11:
			case 18:
			case 20:
			case 21:
				m_navigation[row][col] = false;
				break;
			}
		}
	}
}
void GamePlay::setupTexture()
{
	sf::FloatRect offset = TextureManager::getRect("splash");
	float top = offset.top;
	float left = offset.left;
	float width = static_cast<float>(TextureManager::texture.getSize().x);
	float height = static_cast<float>(TextureManager::texture.getSize().y);
	m_background.append({ { 0,0 },{ 0,0 } });
	m_background.append({ { 0,width },{ 0,width } });
	m_background.append({ { height,width },{ height,width } });

	m_background.append({ { 0,0 },{ 0,0 } });
	m_background.append({ { height,width },{ height,width } });
	m_background.append({ { height,0 },{ height,0 } });

	loadBaseFile();
	setupBaseVertexes(sf::Vector2f{ left,top });
	loadItemsFile();
	setupBaseItemsVertexes(sf::Vector2f{ left,top });
	m_newTexture.create(static_cast<int>(width), static_cast<int>(height));
	m_newTexture.draw(m_background, &TextureManager::texture);
	m_newTexture.display();
	m_background.clear();

	m_background.append({ { 16,16 },{ left,top } });
	m_background.append({ { 16,528 },{ left, top +512 } });
	m_background.append({ { 528,528 },{ left + 512,top + 512 } });

	m_background.append({ { 16,16 },{ left,top } });
	m_background.append({ { 528,528 },{ left+512,top + 512 } });
	m_background.append({ { 528,16 },{ left + 512, top } });
}
Direction GamePlay::newDirection(Direction default)
{
	int choice{ std::rand() % 6 };
	if (choice > 3)
	{
		return default;
	}
	return static_cast<Direction>(choice);
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

void GamePlay::setupBaseVertexes(sf::Vector2f targetOffset)
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
					vertex.position = sf::Vector2f{ col * TILE_SIZE,row * TILE_SIZE }+targetOffset;
					vertex.texCoords = sf::Vector2f{ (m_baseLevel[row][col] % GRIDSIZE)*TILE_SIZE,(m_baseLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
					break;
				case 1:
					vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE }+targetOffset;
					vertex.texCoords = sf::Vector2f{ (m_baseLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(m_baseLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
					break;
				case 2:
				case 4:
					vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE + TILE_SIZE }+targetOffset;
					vertex.texCoords = sf::Vector2f{ (m_baseLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(m_baseLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
					break;
				case 5:
					vertex.position = sf::Vector2f{ col * TILE_SIZE, row * TILE_SIZE + TILE_SIZE }+targetOffset;
					vertex.texCoords = sf::Vector2f{ (m_baseLevel[row][col] % GRIDSIZE)*TILE_SIZE ,(m_baseLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
					break;
				}
				m_background.append(vertex);
			}
		}
	}
}

void GamePlay::setupBaseItemsVertexes(sf::Vector2f targetOffset)
{
	sf::Vector2f offset{ m_textureCoOrds.left, m_textureCoOrds.top };
	for (int row = 0; row < TILES_HIGH; row++)
	{
		for (int col = 0; col < TILES_WIDE; col++)
		{
			if (m_itemsLevel[row][col] == ICE_POOL)
			{
				for (int i = 0; i < 6; i++)
				{
					sf::Vertex vertex;
					switch (i)
					{
					case 0:
					case 3:
						vertex.position = sf::Vector2f{ col * TILE_SIZE,row * TILE_SIZE } +targetOffset;
						vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
						break;
					case 1:
						vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE } +targetOffset;
						vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
						break;
					case 2:
					case 4:
						vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE + TILE_SIZE } +targetOffset;
						vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
						break;
					case 5:
						vertex.position = sf::Vector2f{ col * TILE_SIZE, row * TILE_SIZE + TILE_SIZE } +targetOffset;
						vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE ,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
						break;
					}
					m_background.append(vertex);
				}
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
			if (m_itemsLevel[row][col] != 0 && m_itemsLevel[row][col] != ICE_POOL)
			{
				for (int i = 0; i < 6; i++)
				{
					sf::Vertex vertex;
					switch (i)
					{
					case 0:
					case 3:
						vertex.position = sf::Vector2f{ col * TILE_SIZE,row * TILE_SIZE } +TOP_LEFT;
						vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
						break;
					case 1:
						vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE } +TOP_LEFT;
						vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
						break;
					case 2:
					case 4:
						vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE + TILE_SIZE } +TOP_LEFT;
						vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
						break;
					case 5:
						vertex.position = sf::Vector2f{ col * TILE_SIZE, row * TILE_SIZE + TILE_SIZE } +TOP_LEFT;
						vertex.texCoords = sf::Vector2f{ (m_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE ,(m_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
						break;
					}
					m_foreground.append(vertex);
				}
			}
		}
	}
}


