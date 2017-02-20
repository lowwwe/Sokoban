#include "MainMenu.h"
#include "TextureManager.h"
#include "Game.h"



MainMenu::MainMenu(sf::Font & font) :
	m_font{ font },
	m_buttons{sf::Triangles},
	m_texts{{}},
	m_buttonSelected{-1}
{
	setupButtons();
}


MainMenu::~MainMenu()
{
}

void MainMenu::update(sf::Time deltaTime)
{
	if (m_buttonSelected != -1)
	{
		switch (m_buttonSelected)
		{
		case 0:
			Game::currentState = GameState::Game;
			break;
		case 1:
			Game::currentState = GameState::Help;
			break;
		case 2:
			Game::currentState = GameState::Credits;
			break;
		case 3:
			Game::currentState = GameState::Exit;
			break;

		default:
			break;
		}
	}
	m_buttonSelected = -1;
}

void MainMenu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	window.draw(m_buttons, &TextureManager::texture);
	for (size_t i = 0; i < 4; i++)
	{
		window.draw(m_texts[i]);
	}	
	window.display();
}

void MainMenu::processEvents(sf::Event & event)
{
	if (sf::Event::MouseButtonReleased == event.type)
	{
		
		for (size_t i = 0; i < MAXBUTTONS; i++)
		{
			float left = Game::screenWidth, top = Game::screenHeight, right = 0, bottom = 0;
			for (size_t j = 0; j < 6; j++)
			{
				if (m_buttons[i * 6 + j].position.x < left)
				{
					left = m_buttons[i * 6 + j].position.x;
				}
				if (m_buttons[i * 6 + j].position.x > right)
				{
					right = m_buttons[i * 6 + j].position.x;
				}
				if (m_buttons[i * 6 + j].position.y > bottom)
				{
					bottom = m_buttons[i * 6 + j].position.y;
				}
				if (m_buttons[i * 6 + j].position.y < top)
				{
					top = m_buttons[i * 6 + j].position.y;
				}
			}
			if (event.mouseButton.x > left && event.mouseButton.x < right
				&& event.mouseButton.y > top && event.mouseButton.y < bottom)
			{
				m_buttonSelected = i;
			}
		}
	}
}

void MainMenu::setupButtons()
{
	sf::FloatRect coOrds = TextureManager::getRect("button");
	createButton(m_texts[0], "Play New Game");
	addButton(m_texts[0], sf::Vector2f(300, 100), coOrds);

	createButton(m_texts[1], "Help");
	addButton(m_texts[1], sf::Vector2f(300, 200), coOrds);

	createButton(m_texts[2], "Credits\nLegal");
	addButton(m_texts[2], sf::Vector2f(300, 300), coOrds);

	createButton(m_texts[3], "Exit");
	addButton(m_texts[3], sf::Vector2f(300, 400), coOrds);
	
}

void MainMenu::createButton(sf::Text & Text, std::string message)
{
	Text.setFont(m_font);
	Text.setCharacterSize(24);
	Text.setColor(sf::Color::Yellow);
	Text.setString(message);
}

void MainMenu::addButton(sf::Text & text, sf::Vector2f & position, sf::FloatRect & coOrds)
{
	sf::FloatRect bounds =  text.getGlobalBounds();
	float width{ bounds.width + 40};
	float height{ bounds.height + 20};
	position.x -= width / 2;
	text.setPosition(position.x + 20, position.y +3);
	m_buttons.append(sf::Vertex{ position, sf::Vector2f{coOrds.left, coOrds.top} });
	m_buttons.append(sf::Vertex{ sf::Vector2f{ position.x + width, position.y }, sf::Vector2f{ coOrds.left + coOrds.width,coOrds.top } });
	m_buttons.append(sf::Vertex{ sf::Vector2f{ position.x + width, position.y + height }, sf::Vector2f{ coOrds.left + coOrds.width,coOrds.top + coOrds.height } });

	m_buttons.append(sf::Vertex{ position, sf::Vector2f{ coOrds.left, coOrds.top } });
	m_buttons.append(sf::Vertex{ sf::Vector2f{ position.x + width, position.y + height }, sf::Vector2f{ coOrds.left + coOrds.width,coOrds.top + coOrds.height } });
	m_buttons.append(sf::Vertex{ sf::Vector2f{ position.x , position.y + height }, sf::Vector2f{ coOrds.left ,coOrds.top + coOrds.height } });
}
