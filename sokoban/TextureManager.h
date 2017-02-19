#ifndef TEXTUREMANAGER
#define TEXTUREMANAGER

#include <SFML\Graphics.hpp>

struct SpritInfo
{
	std::string name;
	sf::FloatRect coOrds;
};

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	static void loadData();

	static sf::FloatRect getRect(std::string name);
	static sf::Texture texture;
	
private:
	static std::vector<SpritInfo> m_atlas;
};

#endif // !TEXTUREMANAGER