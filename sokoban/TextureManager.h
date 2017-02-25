#ifndef TEXTUREMANAGER
#define TEXTUREMANAGER

#include <SFML\Graphics.hpp>

const float TILE_SIZE{ 32.0f }; // how wide our sprite tiles are
const sf::Vector2f TOP_LEFT{ 16.0f,16.0f };



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