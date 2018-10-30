#pragma once
#include "ResourceManager.h"
#include <SFML/Graphics/Font.hpp>

namespace Kengine
{
	class FontManager : public ResourceManager<FontManager, sf::Font>
	{
	public:
		FontManager(const std::string& pathFile)
			: ResourceManager(pathFile)
		{
		}

		sf::Font* Load(const std::string& path)
		{
			sf::Font* font = new sf::Font();
			if (!font->loadFromFile(path))
			{
				delete font;
				font = nullptr;
				std::cerr << "! Failed to load Font: " << path << std::endl;
			}
			return font;
		}
	};
}
