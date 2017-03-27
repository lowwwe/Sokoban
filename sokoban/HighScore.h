#ifndef HIGH_SCORE
#define HIGH_SCORE

#include <SFML\Graphics.hpp>
const int MAX_SCORES { 10};




class HighScore
{
	const sf::Vector2f INPUT_OFFSET{ 160.0f, 450.0f };
	const int MAX_LETTERS{ 12 };

	sf::Font m_font; // font used
	sf::Text m_scoresText[MAX_SCORES]; //
	double m_scoreValue[MAX_SCORES];
	sf::Text m_nameInput;
	sf::Text m_promptText;
	sf::Time  m_newScore;
	sf::RectangleShape m_inputBox;
	sf::VertexArray m_iBar;
	bool m_addScore; // are we adding a new score?
	int m_iBarCount;
	bool m_showIBar;
	std::string m_newName;
public:
	HighScore(sf::Font & font);
	~HighScore();
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
	void processEvents(sf::Event & event);
	void loadScores();
	void saveScores();
	void addName();

	static sf::Time  s_newHighScore;
	bool m_showOnly;
	
};

#endif // !HIGH_SCORE
