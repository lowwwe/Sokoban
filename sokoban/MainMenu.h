#ifndef MANIMENU
#define MANIMENU

#include <SFML\Graphics.hpp>


#define MAXBUTTONS 4
class MainMenu
{
public:
	MainMenu(sf::Font & font);
	~MainMenu();
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
	void processEvents(sf::Event & event);
private:
	void setupButtons();
	void createButton(sf::Text & Text, std::string message);
	void addButton(sf::Text & Text, sf::Vector2f & position, sf::FloatRect & coOrds);
	sf::VertexArray m_buttons;
	sf::Font m_font;
	sf::Text m_texts[MAXBUTTONS];
	sf::Text button1;
	int m_buttonSelected; // used to determine whihc button was pressed
};

#endif // !MANIMENU