#include "GamePlay.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"



bool GamePlay::s_navigation[TILES_WIDE][TILES_HIGH];
int GamePlay::s_itemsLevel[TILES_WIDE][TILES_HIGH];

GamePlay::GamePlay(sf::Font & font) :
	m_font{ font },
	m_background{ sf::Triangles },
	m_foreground{ sf::Triangles },
	m_penguinVertexes{ sf::Triangles },
	m_penguins{ {} },
	m_player{},
	m_timer{ sf::seconds(0) },
	m_gameOver{ false },
	m_pushing{ false },
	m_shoving{ false },
	m_countDownTimer{ 0 }
{
	m_textureCoOrds = TextureManager::getRect("tiles");
	m_clock.setFont(m_font);
	m_clock.setCharacterSize(20);
	m_clock.setColor(sf::Color::White);
	m_clock.setPosition(sf::Vector2f{ 500.0f,550.0f });
	setupLevel(1);
}


GamePlay::~GamePlay()
{
}
bool GamePlay::penguinMovement(sf::Time deltaTime)
{
	bool allDead{ true };
	for (size_t i = 0; i < MAX_PENGUIN; i++)
	{
		bool moved{ false };
		m_penguins[i].fadeFootSteps();
		if (m_penguins[i].m_alive)
		{
			allDead = false;
			m_penguins[i].update(deltaTime);
			int row = m_penguins[i].m_square.x;
			int col = m_penguins[i].m_square.y;
			
			if (s_itemsLevel[row][col] == BUCKET1 ||
				s_itemsLevel[row][col] == BUCKET2 ||
				s_itemsLevel[row][col] == BUCKET3)
			{
				m_penguins[i].drown();
			}
			addPenguinVertexes(i);
			if (m_penguins[i].m_ready)
			{
				
				if (s_itemsLevel[row][col] == ICE_POOL)
				{
					m_penguins[i].drown();
					moved = true; // ensure penguin doenst move
				}
				while (!moved)
				{
					switch (m_penguins[i].m_facing)
					{
					case Direction::Down:
						if (s_navigation[row + 1][col])
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
						if (s_navigation[row][col - 1])
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
						if (s_navigation[row][col + 1])
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
						if (s_navigation[row - 1][col])
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
	return allDead;
}

void GamePlay::update(sf::Time deltaTime)
{
	updateClock(deltaTime);
	m_penguinVertexes.clear();
	updateBuckets(deltaTime);
	addBucketVertexes();
	m_player.update(deltaTime);
	m_player.fadeFootSteps();
	playerMovement();
	for (size_t j = 0; j < 6; j++)
	{
		m_penguinVertexes.append(m_player.m_vertexes[j]);
	}
	if(penguinMovement(deltaTime)) // true when all dead
	{ 
		if (s_itemsLevel[m_player.m_square.x][m_player.m_square.y] == EXIT)
		{
			m_gameOver = true;
			m_countDownTimer = 120;
		}
	}
	if (m_gameOver)
	{
		if (m_countDownTimer-- < 0)
		{
			Game::currentState = GameState::MainMenu;
			setupLevel(2);
			m_gameOver = false;
		}
	}
}

void GamePlay::playerMovement()
{
	int row = m_player.m_square.x;
	int col = m_player.m_square.y;
	bool moved{ false };
	bool shove{ false };
	if (m_player.m_ready)
	{
		if (m_shoving || m_pushing)
		{
			if (!moved && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
				&& s_navigation[row + 2][col] &&
				(
					s_itemsLevel[row + 1][col] == BUCKET1 ||
					s_itemsLevel[row + 1][col] == BUCKET2 ||
					s_itemsLevel[row + 1][col] == BUCKET3))
			{
				s_itemsLevel[row + 2][col] = s_itemsLevel[row + 1][col];
				s_itemsLevel[row + 1][col] = 0;
				m_player.move(Direction::Down);
				moveBucket(sf::Vector2i{ row + 1,col }, Direction::Down, m_shoving);

				setupNavigation();
				moved = true;
			}

			if (!moved && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
				&& s_navigation[row - 2][col] &&
				(
					s_itemsLevel[row - 1][col] == BUCKET1 ||
					s_itemsLevel[row - 1][col] == BUCKET2 ||
					s_itemsLevel[row - 1][col] == BUCKET3))
			{
				s_itemsLevel[row - 2][col] = s_itemsLevel[row - 1][col];
				s_itemsLevel[row - 1][col] = 0;
				moveBucket(sf::Vector2i{ row - 1,col }, Direction::Up, m_shoving);
				setupNavigation();
				//m_player.move(Direction::Up);
				moved = true;
			}
			if (!moved && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
				&& s_navigation[row][col - 2] &&
				(
					s_itemsLevel[row][col - 1] == BUCKET1 ||
					s_itemsLevel[row][col - 1] == BUCKET2 ||
					s_itemsLevel[row][col - 1] == BUCKET3))
			{
				s_itemsLevel[row][col - 2] = s_itemsLevel[row][col - 1];
				s_itemsLevel[row][col - 1] = 0;
				moveBucket(sf::Vector2i{ row ,col - 1 }, Direction::Left, m_shoving);
				setupNavigation();
				//m_player.move(Direction::Left);
				moved = true;
			}
			if (!moved && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
				&& s_navigation[row][col + 2] &&
				(
					s_itemsLevel[row][col + 1] == BUCKET1 ||
					s_itemsLevel[row][col + 1] == BUCKET2 ||
					s_itemsLevel[row][col + 1] == BUCKET3))
			{
				s_itemsLevel[row][col + 2] = s_itemsLevel[row][col + 1];
				s_itemsLevel[row][col + 1] = 0;
				moveBucket(sf::Vector2i{ row ,col + 1 }, Direction::Right, m_shoving);
				setupNavigation();
				//m_player.move(Direction::Right);
				moved = true;
			}
		}
		if (!m_pushing && !m_shoving)
		{
			if (!moved && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
				&& s_navigation[row + 1][col])
			{
				m_player.move(Direction::Down);
				moved = true;
			}
			if (!moved && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
				&& s_navigation[row - 1][col])
			{
				m_player.move(Direction::Up);
				moved = true;
			}
			if (!moved && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
				&& s_navigation[row][col - 1])
			{
				m_player.move(Direction::Left);
				moved = true;
			}
			if (!moved && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
				&& s_navigation[row][col + 1])
			{
				m_player.move(Direction::Right);
				moved = true;
			}
		}
	}
}


void GamePlay::moveBucket(sf::Vector2i square, Direction direction, bool shove)
{
	bool found{ false };
	for (Bucket &var : m_buckets)
	{
		if (var.m_square == square)
		{
			var.move(direction);
			var.m_shoved = shove ;
		}
	}
}

void GamePlay::updateBuckets(sf::Time deltaTime)
{
	for(Bucket &var : m_buckets)
	{
		for (int i = 0; i < 6; i++)
		{
			var.update(deltaTime);
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
	window.draw(m_player.m_footSteps);
	window.draw(m_penguinVertexes, &m_newTexture.getTexture());
	window.draw(m_foreground, &m_newTexture.getTexture());
	window.draw(m_clock);
	
}

void GamePlay::processEvents(sf::Event & event)
{
	if (sf::Event::KeyReleased == event.type)
	{
		if (sf::Keyboard::Key::LShift == event.key.code)
		{
			m_pushing = false;
		}
		if (sf::Keyboard::Key::LAlt == event.key.code)
		{
			m_shoving = false;
		}
	}
	if (sf::Event::KeyPressed == event.type)
	{
		if (sf::Keyboard::Key::LShift == event.key.code)
		{
			m_pushing = true;
		}
		if (sf::Keyboard::Key::LAlt == event.key.code)
		{
			m_shoving = true;
		}
	}
}

void GamePlay::setupLevel(int level)
{
	
	setupTexture(level);
	loadItemsFile(level);
	setupItemsVertexes();
	setupNavigation();
	while (!s_navigation[m_player.m_square.x][m_player.m_square.x])
	{
		m_player.m_square.x = std::rand() % 16;
		m_player.m_square.y = std::rand() % 16;
	}
	m_player.position();
	s_navigation[m_player.m_square.x][m_player.m_square.y] = false;
	for (int i = 0; i < MAX_PENGUIN; i++)
	{
		while (!s_navigation[m_penguins[i].m_square.x][m_penguins[i].m_square.x])
		{
			m_penguins[i].m_square.x = std::rand() % 16;
			m_penguins[i].m_square.y = std::rand() % 16;
		}
		m_penguins[i].position();
	}
	s_navigation[m_player.m_square.x][m_player.m_square.y] = true;
	setupBuckets();
	
}

void GamePlay::addPenguinVertexes(int index)
{	
	for (int i = 0; i < 6; i++)
	{
		m_penguinVertexes.append(m_penguins[index].m_vertexes[i]);
	}
}
void GamePlay::setupNavigation()
{
	for (int row = 0; row < TILES_HIGH; row++)
	{
		for (int col = 0; col < TILES_WIDE; col++)
		{
			s_navigation[row][col] = true;
			switch (m_baseLevel[row][col])
			{
			case 1:
			case 6:
			case 7:
				s_navigation[row][col] = false;
				break;			
			}
			switch (s_itemsLevel[row][col])
			{
			case 2:
			case 3:
			case 11:
			case 18:
			case 20:
			case 21:
				s_navigation[row][col] = false;
				break;
			}
		}
	}
}
void GamePlay::setupTexture(int level)
{
	sf::FloatRect offset = TextureManager::getRect("splash");
	float top = offset.top;
	float left = offset.left;
	float width = static_cast<float>(TextureManager::texture.getSize().x);
	float height = static_cast<float>(TextureManager::texture.getSize().y);
	m_background.append({ { 0,0 },{ 0,0 } });
	m_background.append({ { width,0 },{ width,0 } });
	m_background.append({ { width,height },{ width,height } });

	m_background.append({ { 0,0 },{ 0,0 } });
	m_background.append({ { width,height },{ width,height } });
	m_background.append({ { 0,height },{ 0,height } });

	loadBaseFile(level);
	setupBaseVertexes(sf::Vector2f{ left,top });
	loadItemsFile(level);
	setupBaseItemsVertexes(sf::Vector2f{ left,top });
	if (!m_newTexture.create(static_cast<int>(width), static_cast<int>(height)))
	{
		std::cout << "problem creating texture" << std::endl;
	}

	sf::Vector2u  size = m_newTexture.getSize();
	m_newTexture.setView(sf::View(sf::FloatRect{ 0.0f,0.0f,static_cast<float>(size.x),static_cast<float>(size.y) }));
	m_newTexture.draw(m_background, &TextureManager::texture);
	 size = m_newTexture.getSize();
	m_newTexture.display();
	 size = m_newTexture.getSize();
	m_background.clear();

	m_background.append({ { 16,16 },{ left,top } });
	m_background.append({ { 16,528 },{ left, top +512 } });
	m_background.append({ { 528,528 },{ left + 512,top + 512 } });

	m_background.append({ { 16,16 },{ left,top } });
	m_background.append({ { 528,528 },{ left+512,top + 512 } });
	m_background.append({ { 528,16 },{ left + 512, top } });
}
void GamePlay::setupBuckets()
{
	for (int row = 0; row < TILES_HIGH; row++)
	{
		for (int col = 0; col < TILES_WIDE; col++)
		{
			if (s_itemsLevel[row][col] == BUCKET1 ||
				s_itemsLevel[row][col] == BUCKET2 ||
				s_itemsLevel[row][col] == BUCKET3)
			{
				m_buckets.push_back(Bucket{ sf::Vector2i{row,col}, s_itemsLevel[row][col] });
			}
		}
	}
}
void GamePlay::addBucketVertexes()
{
	for each (Bucket var in	m_buckets)
	{
		for (int i = 0; i < 6; i++)
		{
			m_penguinVertexes.append(var.m_vertexes[i]);
		}
	}
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
void GamePlay::updateClock(sf::Time deltaTime)
{
	std::string time;
	if (!m_gameOver)
	{
		m_timer += deltaTime;
	}
	int min = static_cast<int>( m_timer.asSeconds()) / 60;
	int seconds = static_cast<int>(m_timer.asSeconds()) % 60;
	int hundreds = static_cast<int>((m_timer.asSeconds() * 100.0f) - (seconds * 100.0f));
	if(min >0)
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
	if (m_gameOver)
	{
		time += "." + std::to_string(hundreds);
	}
	m_clock.setString(time);
}
void GamePlay::loadBaseFile(int level)
{
	std::ifstream infile;
	std::string name;
	std::string equals;
	sf::IntRect coords;
	int i{ 0 };
	infile.open("ASSETS\\IMAGES\\level" + std::to_string(level) + ".txt");
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
			if (s_itemsLevel[row][col] == ICE_POOL)
			{
				for (int i = 0; i < 6; i++)
				{
					sf::Vertex vertex;
					switch (i)
					{
					case 0:
					case 3:
						vertex.position = sf::Vector2f{ col * TILE_SIZE,row * TILE_SIZE } +targetOffset;
						vertex.texCoords = sf::Vector2f{ (s_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE,(s_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
						break;
					case 1:
						vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE } +targetOffset;
						vertex.texCoords = sf::Vector2f{ (s_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(s_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
						break;
					case 2:
					case 4:
						vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE + TILE_SIZE } +targetOffset;
						vertex.texCoords = sf::Vector2f{ (s_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(s_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
						break;
					case 5:
						vertex.position = sf::Vector2f{ col * TILE_SIZE, row * TILE_SIZE + TILE_SIZE } +targetOffset;
						vertex.texCoords = sf::Vector2f{ (s_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE ,(s_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
						break;
					}
					m_background.append(vertex);
				}
			}
		}
	}
}

void GamePlay::loadItemsFile(int level)
{
	std::ifstream infile;
	std::string name;
	std::string equals;
	sf::IntRect coords;
	int i{ 0 };
	infile.open("ASSETS\\IMAGES\\items" + std::to_string(level) + ".txt");
	while (!infile.eof() && i < TILES_HIGH)
	{
		infile >> s_itemsLevel[i][0] >> s_itemsLevel[i][1] >> s_itemsLevel[i][2] >> s_itemsLevel[i][3]
			>> s_itemsLevel[i][4] >> s_itemsLevel[i][5] >> s_itemsLevel[i][6] >> s_itemsLevel[i][7]
			>> s_itemsLevel[i][8] >> s_itemsLevel[i][9] >> s_itemsLevel[i][10] >> s_itemsLevel[i][11]
			>> s_itemsLevel[i][12] >> s_itemsLevel[i][13] >> s_itemsLevel[i][14] >> s_itemsLevel[i][15];
		i++;
	}
	infile.close();
}

void GamePlay::setupItemsVertexes()
{
	sf::Vector2f offset{ m_textureCoOrds.left, m_textureCoOrds.top };
	m_foreground.clear();
	for (int row = 0; row < TILES_HIGH; row++)
	{
		for (int col = 0; col < TILES_WIDE; col++)
		{
			if (s_itemsLevel[row][col] != 0 && !(
				s_itemsLevel[row][col] == ICE_POOL ||
				s_itemsLevel[row][col] == BUCKET1 ||
				s_itemsLevel[row][col] == BUCKET2 ||
				s_itemsLevel[row][col] == BUCKET3 
				))
			{
				for (int i = 0; i < 6; i++)
				{
					sf::Vertex vertex;
					switch (i)
					{
					case 0:
					case 3:
						vertex.position = sf::Vector2f{ col * TILE_SIZE,row * TILE_SIZE } +TOP_LEFT;
						vertex.texCoords = sf::Vector2f{ (s_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE,(s_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
						break;
					case 1:
						vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE } +TOP_LEFT;
						vertex.texCoords = sf::Vector2f{ (s_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(s_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE } +offset;
						break;
					case 2:
					case 4:
						vertex.position = sf::Vector2f{ col * TILE_SIZE + TILE_SIZE,row * TILE_SIZE + TILE_SIZE } +TOP_LEFT;
						vertex.texCoords = sf::Vector2f{ (s_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE + TILE_SIZE,(s_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
						break;
					case 5:
						vertex.position = sf::Vector2f{ col * TILE_SIZE, row * TILE_SIZE + TILE_SIZE } +TOP_LEFT;
						vertex.texCoords = sf::Vector2f{ (s_itemsLevel[row][col] % GRIDSIZE)*TILE_SIZE ,(s_itemsLevel[row][col] / GRIDSIZE)*TILE_SIZE + TILE_SIZE } +offset;
						break;
					}
					m_foreground.append(vertex);
				}
			}
		}
	}
}


