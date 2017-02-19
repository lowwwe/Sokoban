#include "MainMenu.h"
#include "TextureManager.h"



MainMenu::MainMenu(sf::Font & font) :
	m_font{ font },
	m_buttons{sf::Triangles},
	m_texts{{}}
{
	setupButtons();
}


MainMenu::~MainMenu()
{
}

void MainMenu::update(sf::Time deltaTime)
{
}

void MainMenu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	window.draw(m_buttons, &TextureManager::texture);
	window.draw(m_texts[0]);
	window.display();
}

void MainMenu::processEvents(sf::Event & event)
{
}

void MainMenu::setupButtons()
{
	sf::FloatRect coOrds = TextureManager::getRect("button");
	createButton(m_texts[0], "Play New Game");
	addButton(m_texts[0], sf::Vector2f(300, 100), coOrds);
	
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
