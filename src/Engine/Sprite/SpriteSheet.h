#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Kengine
{
	enum class Direction{ Right = 0, Left };

	class TextureManager;
	class AnimationBase;
	class AnimationDirectional;
	
	class SpriteSheet
	{
		std::string m_texture;
		sf::Sprite m_sprite;
		sf::Vector2i m_spriteSize;
		sf::Vector2f m_spriteScale;
		Direction m_direction;
		std::string m_animationType;

		std::unordered_map<std::string, AnimationBase*> m_animations;
		AnimationBase* m_animationCurrent;
		TextureManager* m_textureManager;

		void ReleaseSheet();
	public:
		SpriteSheet(TextureManager* textureManager)
			: m_direction(Direction::Right), 
			  m_animationCurrent(nullptr),
			  m_textureManager(textureManager)
		{
		}

		void SetSpritePosition(const sf::Vector2f& pos);
		bool SetAnimation(const std::string& name, const bool& play, const bool& loop = false);

		bool LoadSheet(const std::string& filePath);

		void Update(const float& deltaTime);
		void Draw(sf::RenderWindow* window);

		sf::Vector2i GetSpriteSize() const;
		Direction GetDirection();
		void CropSprite(const sf::IntRect& rect);
		void SetDirection(const Direction& direction);
	};
}

