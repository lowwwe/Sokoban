#ifndef HIGH_SCORE
#define HIGH_SCORE

#include <SFML\Graphics.hpp>
const int MAX_SCORES = 3;




class HighScore
{
	sf::Font m_font; // font used
	sf::Text m_scoresText[MAX_SCORES]; //
	sf::Text m_nameInput;
	sf::Text m_promptText;
	sf::Time  m_newScore;
public:
	HighScore(sf::Font & font);
	~HighScore();
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
	void processEvents(sf::Event & event);

	static sf::Time  s_newHighScore;
	bool m_showOnly;
	
};

#endif // !HIGH_SCORE